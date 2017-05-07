#include "dtexture.h"
#include "ddir.h"

namespace de {
DTexture::DTexture()
{
}

DTexture::~DTexture()
{
}

void DTexture::vglLoadDDS(const char* filename, vglImageData* image)
{
	FILE* f;
	de::DDir *dir = new de::DDir();
	char* full_path = dir->get_dir(filename);

	memset(image, 0, sizeof(*image));

	f = fopen(full_path, "rb");

	delete dir;

	if (f == NULL)
		return;

	DDS_FILE_HEADER file_header = { 0, };

	fread(&file_header, sizeof(file_header.magic) + sizeof(file_header.std_header), 1, f);

	if (file_header.magic != DDS_MAGIC)
	{
		goto done_close_file;
	}

	if (file_header.std_header.ddspf.dwFourCC == DDS_FOURCC_DX10)
	{
		fread(&file_header.dxt10_header, sizeof(file_header.dxt10_header), 1, f);
	}

	if (!vgl_DDSHeaderToImageDataHeader(file_header, image))
		goto done_close_file;

	image->target = vgl_GetTargetFromDDSHeader(file_header);

	if (image->target == GL_NONE)
		goto done_close_file;

	size_t current_pos = ftell(f);
	size_t file_size;
	fseek(f, 0, SEEK_END);
	file_size = ftell(f);
	fseek(f, (long)current_pos, SEEK_SET);

	image->totalDataSize = file_size - current_pos;
	image->mip[0].data = new uint8_t[image->totalDataSize];

	fread(image->mip[0].data, file_size - current_pos, 1, f);

	int level;
	GLubyte * ptr = reinterpret_cast<GLubyte*>(image->mip[0].data);

	int width = file_header.std_header.width;
	int height = file_header.std_header.height;
	int depth = file_header.std_header.depth;

	image->sliceStride = 0;

	if (image->mipLevels == 0)
	{
		image->mipLevels = 1;
	}

	for (level = 0; level < image->mipLevels; ++level)
	{
		image->mip[level].data = ptr;
		image->mip[level].width = width;
		image->mip[level].height = height;
		image->mip[level].depth = depth;
		image->mip[level].mipStride = vgl_GetDDSStride(file_header, width) * height;
		image->sliceStride += image->mip[level].mipStride;
		ptr += image->mip[level].mipStride;
		width >>= 1;
		height >>= 1;
		depth >>= 1;
	}

done_close_file:
	fclose(f);
}

bool DTexture::vgl_DDSHeaderToImageDataHeader(const DDS_FILE_HEADER& header, vglImageData* image)
{
	if (header.std_header.ddspf.dwFlags == DDS_DDPF_FOURCC &&
		header.std_header.ddspf.dwFourCC == DDS_FOURCC_DX10)
	{
		if (header.dxt10_header.format < NUM_DDS_FORMATS)
		{
			const DDS_FORMAT_GL_INFO& format = gl_info_table[header.dxt10_header.format];
			image->format = format.format;
			image->type = format.type;
			image->internalFormat = format.internalFormat;
			image->swizzle[0] = format.swizzle_r;
			image->swizzle[1] = format.swizzle_g;
			image->swizzle[2] = format.swizzle_b;
			image->swizzle[3] = format.swizzle_a;
			image->mipLevels = header.std_header.mip_levels;
			return true;
		}
	}
	else if (header.std_header.ddspf.dwFlags == DDS_DDPF_FOURCC)
	{
		image->swizzle[0] = GL_RED;
		image->swizzle[1] = GL_GREEN;
		image->swizzle[2] = GL_BLUE;
		image->swizzle[3] = GL_ALPHA;
		image->mipLevels = header.std_header.mip_levels;

		switch (header.std_header.ddspf.dwFourCC)
		{
		case 116:
			image->format = GL_RGBA;
			image->type = GL_FLOAT;
			image->internalFormat = GL_RGBA32F;
			/*
			image->swizzle[0] = GL_ALPHA;
			image->swizzle[1] = GL_BLUE;
			image->swizzle[2] = GL_GREEN;
			image->swizzle[3] = GL_RED;
			*/
			return true;
		default:
			break;
		}
	}
	else
	{
		image->swizzle[0] = GL_RED;
		image->swizzle[1] = GL_GREEN;
		image->swizzle[2] = GL_BLUE;
		image->swizzle[3] = GL_ALPHA;
		image->mipLevels = header.std_header.mip_levels;

		switch (header.std_header.ddspf.dwFlags)
		{
		case DDS_DDPF_RGB:
			image->format = GL_BGR;
			image->type = GL_UNSIGNED_BYTE;
			image->internalFormat = GL_RGB8;
			image->swizzle[3] = GL_ONE;
			return true;
		case (DDS_DDPF_RGB | DDS_DDPF_ALPHA):
		case (DDS_DDPF_RGB | DDS_DDPF_ALPHAPIXELS):
			image->format = GL_BGRA;
			image->type = GL_UNSIGNED_BYTE;
			image->internalFormat = GL_RGBA8;
			return true;
		case DDS_DDPF_ALPHA:
			image->format = GL_RED;
			image->type = GL_UNSIGNED_BYTE;
			image->internalFormat = GL_R8;
			image->swizzle[0] = image->swizzle[1] = image->swizzle[2] = GL_ZERO;
			image->swizzle[3] = GL_RED;
			return true;
		case DDS_DDPF_LUMINANCE:
			image->format = GL_RED;
			image->type = GL_UNSIGNED_BYTE;
			image->internalFormat = GL_R8;
			image->swizzle[0] = image->swizzle[1] = image->swizzle[2] = GL_RED;
			image->swizzle[3] = GL_ONE;
			return true;
		case (DDS_DDPF_LUMINANCE | DDS_DDPF_ALPHA):
			image->format = GL_RG;
			image->type = GL_UNSIGNED_BYTE;
			image->internalFormat = GL_RG8;
			image->swizzle[0] = image->swizzle[1] = image->swizzle[2] = GL_RED;
			image->swizzle[3] = GL_GREEN;
			return true;
		default:
			break;
		}
	}

	image->format = image->type = image->internalFormat = GL_NONE;
	image->swizzle[0] = image->swizzle[1] = image->swizzle[2] = image->swizzle[3] = GL_ZERO;

	return false;
}

GLsizei DTexture::vgl_GetDDSStride(const DDS_FILE_HEADER& header, GLsizei width)
{
	if (header.std_header.ddspf.dwFlags == DDS_DDPF_FOURCC &&
		header.std_header.ddspf.dwFourCC == DDS_FOURCC_DX10)
	{
		if (header.dxt10_header.format < NUM_DDS_FORMATS)
		{
			const DDS_FORMAT_GL_INFO& format = gl_info_table[header.dxt10_header.format];
			return (format.bits_per_texel * width + 7) / 8;
		}
	}
	else
	{
		switch (header.std_header.ddspf.dwFlags)
		{
		case DDS_DDPF_RGB:
			return width * 3;
		case (DDS_DDPF_RGB | DDS_DDPF_ALPHA):
		case (DDS_DDPF_RGB | DDS_DDPF_ALPHAPIXELS):
			return width * 4;
		case DDS_DDPF_ALPHA:
			return width;
		default:
			break;
		}
	}

	return 0;
}

GLenum DTexture::vgl_GetTargetFromDDSHeader(const DDS_FILE_HEADER& header)
{
	// If the DX10 header is present it's format should be non-zero (unless it's unknown)
	if (header.dxt10_header.format != 0)
	{
		// Check the dimension...
		switch (header.dxt10_header.dimension)
		{
			// Could be a 1D or 1D array texture
		case DDS_RESOURCE_DIMENSION_TEXTURE1D:
			if (header.dxt10_header.array_size > 1)
			{
				return GL_TEXTURE_1D_ARRAY;
			}
			return GL_TEXTURE_1D;
			// 2D means 2D, 2D array, cubemap or cubemap array
		case DDS_RESOURCE_DIMENSION_TEXTURE2D:
			if (header.dxt10_header.misc_flag & DDS_RESOURCE_MISC_TEXTURECUBE)
			{
				if (header.dxt10_header.array_size > 1)
					return GL_TEXTURE_CUBE_MAP_ARRAY;
				return GL_TEXTURE_CUBE_MAP;
			}
			if (header.dxt10_header.array_size > 1)
				return GL_TEXTURE_2D_ARRAY;
			return GL_TEXTURE_2D;
			// 3D should always be a volume texture
		case DDS_RESOURCE_DIMENSION_TEXTURE3D:
			return GL_TEXTURE_3D;
		}
		return GL_NONE;
	}

	// No DX10 header. Check volume texture flag
	if (header.std_header.caps2 & DDSCAPS2_VOLUME)
		return GL_TEXTURE_3D;

	// Could be a cubemap
	if (header.std_header.caps2 & DDSCAPS2_CUBEMAP)
	{
		// This shouldn't happen if the DX10 header is present, but what the hey
		if (header.dxt10_header.array_size > 1)
			return GL_TEXTURE_CUBE_MAP_ARRAY;
		else
			return GL_TEXTURE_CUBE_MAP;
	}

	// Alright, if there's no height, guess 1D
	if (header.std_header.height <= 1)
		return GL_TEXTURE_1D;

	// Last ditch, probably 2D
	return GL_TEXTURE_2D;
}

void DTexture::vglLoadImage(const char* filename, vglImageData* image)
{

	vglLoadDDS(filename, image);
}

void DTexture::vglUnloadImage(vglImageData* image)
{
	delete[] reinterpret_cast<uint8_t *>(image->mip[0].data);
}

GLuint DTexture::vglLoadTexture(const char* filename,
	GLuint texture,
	vglImageData* image)
{
	vglImageData local_image;
	int level;

	if (image == 0)
		image = &local_image;

	vglLoadImage(filename, image);

	if (texture == 0)
	{
		gl_->glGenTextures(1, &texture);
	}

	gl_->glBindTexture(image->target, texture);

	GLubyte * ptr = (GLubyte *)image->mip[0].data;

	switch (image->target)
	{
	case GL_TEXTURE_1D:
		gl_->glTexStorage1D(image->target,
			image->mipLevels,
			image->internalFormat,
			image->mip[0].width);
		for (level = 0; level < image->mipLevels; ++level)
		{
			gl_->glTexSubImage1D(GL_TEXTURE_1D,
				level,
				0,
				image->mip[level].width,
				image->format, image->type,
				image->mip[level].data);
		}
		break;
	case GL_TEXTURE_1D_ARRAY:
		gl_->glTexStorage2D(image->target,
			image->mipLevels,
			image->internalFormat,
			image->mip[0].width,
			image->slices);
		for (level = 0; level < image->mipLevels; ++level)
		{
			gl_->glTexSubImage2D(GL_TEXTURE_1D,
				level,
				0, 0,
				image->mip[level].width, image->slices,
				image->format, image->type,
				image->mip[level].data);
		}
		break;
	case GL_TEXTURE_2D:
		gl_->glTexStorage2D(image->target,
			image->mipLevels,
			image->internalFormat,
			image->mip[0].width,
			image->mip[0].height);
		for (level = 0; level < image->mipLevels; ++level)
		{
			gl_->glTexSubImage2D(GL_TEXTURE_2D,
				level,
				0, 0,
				image->mip[level].width, image->mip[level].height,
				image->format, image->type,
				image->mip[level].data);
		}
		break;
	case GL_TEXTURE_CUBE_MAP:
		for (level = 0; level < image->mipLevels; ++level)
		{
			ptr = (GLubyte *)image->mip[level].data;
			for (int face = 0; face < 6; face++)
			{
				gl_->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
					level,
					image->internalFormat,
					image->mip[level].width, image->mip[level].height,
					0,
					image->format, image->type,
					ptr + image->sliceStride * face);
			}
		}
		break;
	case GL_TEXTURE_2D_ARRAY:
		gl_->glTexStorage3D(image->target,
			image->mipLevels,
			image->internalFormat,
			image->mip[0].width,
			image->mip[0].height,
			image->slices);
		for (level = 0; level < image->mipLevels; ++level)
		{
			gl_->glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
				level,
				0, 0, 0,
				image->mip[level].width, image->mip[level].height, image->slices,
				image->format, image->type,
				image->mip[level].data);
		}
		break;
	case GL_TEXTURE_CUBE_MAP_ARRAY:
		gl_->glTexStorage3D(image->target,
			image->mipLevels,
			image->internalFormat,
			image->mip[0].width,
			image->mip[0].height,
			image->slices);
		break;
	case GL_TEXTURE_3D:
		gl_->glTexStorage3D(image->target,
			image->mipLevels,
			image->internalFormat,
			image->mip[0].width,
			image->mip[0].height,
			image->mip[0].depth);
		for (level = 0; level < image->mipLevels; ++level)
		{
			gl_->glTexSubImage3D(GL_TEXTURE_3D,
				level,
				0, 0, 0,
				image->mip[level].width, image->mip[level].height, image->mip[level].depth,
				image->format, image->type,
				image->mip[level].data);
		}
		break;
	default:
		break;
	}

	gl_->glTexParameteriv(image->target, GL_TEXTURE_SWIZZLE_RGBA, reinterpret_cast<const GLint *>(image->swizzle));

	if (image == &local_image)
	{
		vglUnloadImage(image);
	}

	return texture;
}

void DTexture::set_gl(QOpenGLFunctions_4_3_Core * gl)
{
	gl_ = gl;
}

}

