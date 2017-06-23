#pragma once

#ifndef VDDS_H
#define VDDS_H

#include <qopenglfunctions_4_4_core.h>

#define MAX_TEXTURE_MIPS    14
#define NUM_DDS_FORMATS     (sizeof(gl_info_table) / sizeof(gl_info_table[0]))

struct vglImageMipData
{
	GLsizei width;                              // Width of this mipmap level
	GLsizei height;                             // Height of this mipmap level
	GLsizei depth;                              // Depth pof mipmap level
	GLsizeiptr mipStride;                       // Distance in bytes between mip levels in memory
	GLvoid* data;                               // Pointer to data
};

// This is the main image data structure. It contains all the parameters needed
// to place texture data into a texture object using OpenGL.
struct vglImageData
{
	GLenum target;                              // Texture target (1D, 2D, cubemap, array, etc.)
	GLenum internalFormat;                      // Recommended internal format (GL_RGBA32F, etc).
	GLenum format;                              // Format in memory
	GLenum type;                                // Type in memory (GL_RED, GL_RGB, etc.)
	GLenum swizzle[4];                          // Swizzle for RGBA
	GLsizei mipLevels;                          // Number of present mipmap levels
	GLsizei slices;                             // Number of slices (for arrays)
	GLsizeiptr sliceStride;                     // Distance in bytes between slices of an array texture
	GLsizeiptr totalDataSize;                   // Complete amount of data allocated for texture
	vglImageMipData mip[MAX_TEXTURE_MIPS];      // Actual mipmap data
};

enum DDS_FORMAT
{
	DDS_FORMAT_UNKNOWN = 0,
	DDS_FORMAT_R32G32B32A32_TYPELESS = 1,
	DDS_FORMAT_R32G32B32A32_FLOAT = 2,
	DDS_FORMAT_R32G32B32A32_UINT = 3,
	DDS_FORMAT_R32G32B32A32_SINT = 4,
	DDS_FORMAT_R32G32B32_TYPELESS = 5,
	DDS_FORMAT_R32G32B32_FLOAT = 6,
	DDS_FORMAT_R32G32B32_UINT = 7,
	DDS_FORMAT_R32G32B32_SINT = 8,
	DDS_FORMAT_R16G16B16A16_TYPELESS = 9,
	DDS_FORMAT_R16G16B16A16_FLOAT = 10,
	DDS_FORMAT_R16G16B16A16_UNORM = 11,
	DDS_FORMAT_R16G16B16A16_UINT = 12,
	DDS_FORMAT_R16G16B16A16_SNORM = 13,
	DDS_FORMAT_R16G16B16A16_SINT = 14,
	DDS_FORMAT_R32G32_TYPELESS = 15,
	DDS_FORMAT_R32G32_FLOAT = 16,
	DDS_FORMAT_R32G32_UINT = 17,
	DDS_FORMAT_R32G32_SINT = 18,
	DDS_FORMAT_R32G8X24_TYPELESS = 19,
	DDS_FORMAT_D32_FLOAT_S8X24_UINT = 20,
	DDS_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
	DDS_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
	DDS_FORMAT_R10G10B10A2_TYPELESS = 23,
	DDS_FORMAT_R10G10B10A2_UNORM = 24,
	DDS_FORMAT_R10G10B10A2_UINT = 25,
	DDS_FORMAT_R11G11B10_FLOAT = 26,
	DDS_FORMAT_R8G8B8A8_TYPELESS = 27,
	DDS_FORMAT_R8G8B8A8_UNORM = 28,
	DDS_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
	DDS_FORMAT_R8G8B8A8_UINT = 30,
	DDS_FORMAT_R8G8B8A8_SNORM = 31,
	DDS_FORMAT_R8G8B8A8_SINT = 32,
	DDS_FORMAT_R16G16_TYPELESS = 33,
	DDS_FORMAT_R16G16_FLOAT = 34,
	DDS_FORMAT_R16G16_UNORM = 35,
	DDS_FORMAT_R16G16_UINT = 36,
	DDS_FORMAT_R16G16_SNORM = 37,
	DDS_FORMAT_R16G16_SINT = 38,
	DDS_FORMAT_R32_TYPELESS = 39,
	DDS_FORMAT_D32_FLOAT = 40,
	DDS_FORMAT_R32_FLOAT = 41,
	DDS_FORMAT_R32_UINT = 42,
	DDS_FORMAT_R32_SINT = 43,
	DDS_FORMAT_R24G8_TYPELESS = 44,
	DDS_FORMAT_D24_UNORM_S8_UINT = 45,
	DDS_FORMAT_R24_UNORM_X8_TYPELESS = 46,
	DDS_FORMAT_X24_TYPELESS_G8_UINT = 47,
	DDS_FORMAT_R8G8_TYPELESS = 48,
	DDS_FORMAT_R8G8_UNORM = 49,
	DDS_FORMAT_R8G8_UINT = 50,
	DDS_FORMAT_R8G8_SNORM = 51,
	DDS_FORMAT_R8G8_SINT = 52,
	DDS_FORMAT_R16_TYPELESS = 53,
	DDS_FORMAT_R16_FLOAT = 54,
	DDS_FORMAT_D16_UNORM = 55,
	DDS_FORMAT_R16_UNORM = 56,
	DDS_FORMAT_R16_UINT = 57,
	DDS_FORMAT_R16_SNORM = 58,
	DDS_FORMAT_R16_SINT = 59,
	DDS_FORMAT_R8_TYPELESS = 60,
	DDS_FORMAT_R8_UNORM = 61,
	DDS_FORMAT_R8_UINT = 62,
	DDS_FORMAT_R8_SNORM = 63,
	DDS_FORMAT_R8_SINT = 64,
	DDS_FORMAT_A8_UNORM = 65,
	DDS_FORMAT_R1_UNORM = 66,
	DDS_FORMAT_R9G9B9E5_SHAREDEXP = 67,
	DDS_FORMAT_R8G8_B8G8_UNORM = 68,
	DDS_FORMAT_G8R8_G8B8_UNORM = 69,
	DDS_FORMAT_BC1_TYPELESS = 70,
	DDS_FORMAT_BC1_UNORM = 71,
	DDS_FORMAT_BC1_UNORM_SRGB = 72,
	DDS_FORMAT_BC2_TYPELESS = 73,
	DDS_FORMAT_BC2_UNORM = 74,
	DDS_FORMAT_BC2_UNORM_SRGB = 75,
	DDS_FORMAT_BC3_TYPELESS = 76,
	DDS_FORMAT_BC3_UNORM = 77,
	DDS_FORMAT_BC3_UNORM_SRGB = 78,
	DDS_FORMAT_BC4_TYPELESS = 79,
	DDS_FORMAT_BC4_UNORM = 80,
	DDS_FORMAT_BC4_SNORM = 81,
	DDS_FORMAT_BC5_TYPELESS = 82,
	DDS_FORMAT_BC5_UNORM = 83,
	DDS_FORMAT_BC5_SNORM = 84,
	DDS_FORMAT_B5G6R5_UNORM = 85,
	DDS_FORMAT_B5G5R5A1_UNORM = 86,
	DDS_FORMAT_B8G8R8A8_UNORM = 87,
	DDS_FORMAT_B8G8R8X8_UNORM = 88,
	DDS_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
	DDS_FORMAT_B8G8R8A8_TYPELESS = 90,
	DDS_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
	DDS_FORMAT_B8G8R8X8_TYPELESS = 92,
	DDS_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
	DDS_FORMAT_BC6H_TYPELESS = 94,
	DDS_FORMAT_BC6H_UF16 = 95,
	DDS_FORMAT_BC6H_SF16 = 96,
	DDS_FORMAT_BC7_TYPELESS = 97,
	DDS_FORMAT_BC7_UNORM = 98,
	DDS_FORMAT_BC7_UNORM_SRGB = 99,
	DDS_FORMAT_AYUV = 100,
	DDS_FORMAT_Y410 = 101,
	DDS_FORMAT_Y416 = 102,
	DDS_FORMAT_NV12 = 103,
	DDS_FORMAT_P010 = 104,
	DDS_FORMAT_P016 = 105,
	DDS_FORMAT_420_OPAQUE = 106,
	DDS_FORMAT_YUY2 = 107,
	DDS_FORMAT_Y210 = 108,
	DDS_FORMAT_Y216 = 109,
	DDS_FORMAT_NV11 = 110,
	DDS_FORMAT_AI44 = 111,
	DDS_FORMAT_IA44 = 112,
	DDS_FORMAT_P8 = 113,
	DDS_FORMAT_A8P8 = 114,
	DDS_FORMAT_B4G4R4A4_UNORM = 115
};

enum
{
	DDS_MAGIC = 0x20534444,

	DDSCAPS_COMPLEX = 0x00000008,
	DDSCAPS_MIPMAP = 0x00400000,
	DDSCAPS_TEXTURE = 0x00001000,

	DDSCAPS2_CUBEMAP = 0x00000200,
	DDSCAPS2_CUBEMAP_POSITIVEX = 0x00000400,
	DDSCAPS2_CUBEMAP_NEGATIVEX = 0x00000800,
	DDSCAPS2_CUBEMAP_POSITIVEY = 0x00001000,
	DDSCAPS2_CUBEMAP_NEGATIVEY = 0x00002000,
	DDSCAPS2_CUBEMAP_POSITIVEZ = 0x00004000,
	DDSCAPS2_CUBEMAP_NEGATIVEZ = 0x00008000,
	DDSCAPS2_VOLUME = 0x00200000,

	DDS_CUBEMAP_ALLFACES = (DDSCAPS2_CUBEMAP_POSITIVEX |
	DDSCAPS2_CUBEMAP_NEGATIVEX |
		DDSCAPS2_CUBEMAP_POSITIVEY |
		DDSCAPS2_CUBEMAP_NEGATIVEY |
		DDSCAPS2_CUBEMAP_POSITIVEZ |
		DDSCAPS2_CUBEMAP_NEGATIVEZ),

	DDS_RESOURCE_DIMENSION_UNKNOWN = 0,
	DDS_RESOURCE_DIMENSION_BUFFER = 1,
	DDS_RESOURCE_DIMENSION_TEXTURE1D = 2,
	DDS_RESOURCE_DIMENSION_TEXTURE2D = 3,
	DDS_RESOURCE_DIMENSION_TEXTURE3D = 4,

	DDS_RESOURCE_MISC_TEXTURECUBE = 0x00000004,

	DDS_FOURCC_DX10 = 0x30315844,
	DDS_FOURCC_DXT1 = 0x31545844,
	DDS_FOURCC_DXT2 = 0x32545844,
	DDS_FOURCC_DXT3 = 0x33545844,
	DDS_FOURCC_DXT4 = 0x34545844,
	DDS_FOURCC_DXT5 = 0x35545844,

	DDS_DDPF_ALPHAPIXELS = 0x00000001,
	DDS_DDPF_ALPHA = 0x00000002,
	DDS_DDPF_FOURCC = 0x00000004,
	DDS_DDPF_RGB = 0x00000040,
	DDS_DDPF_YUV = 0x00000200,
	DDS_DDPF_LUMINANCE = 0x00020000,
};

struct DDS_PIXELFORMAT
{
	uint32_t                dwSize;
	uint32_t                dwFlags;
	uint32_t                dwFourCC;
	uint32_t                dwRGBBitCount;
	uint32_t                dwRBitMask;
	uint32_t                dwGBitMask;
	uint32_t                dwBBitMask;
	uint32_t                dwABitMask;
};

struct DDS_HEADER
{
	uint32_t                size;
	uint32_t                flags;
	uint32_t                height;
	uint32_t                width;
	uint32_t                pitch_or_linear_size;
	uint32_t                depth;
	uint32_t                mip_levels;
	uint32_t                reserved[11];
	DDS_PIXELFORMAT         ddspf;
	uint32_t                caps1;
	uint32_t                caps2;
	uint32_t                caps3;
	uint32_t                caps4;
	uint32_t                reserved2;
};

struct DDS_HEADER_DXT10
{
	uint32_t                format;
	uint32_t                dimension;
	uint32_t                misc_flag;
	uint32_t                array_size;
	uint32_t                reserved;
};

struct DDS_FILE_HEADER
{
	uint32_t                magic;
	DDS_HEADER              std_header;
	DDS_HEADER_DXT10        dxt10_header;
};

struct DDS_FORMAT_GL_INFO
{
	GLenum                  format;
	GLenum                  type;
	GLenum                  internalFormat;
	GLenum                  swizzle_r;
	GLenum                  swizzle_g;
	GLenum                  swizzle_b;
	GLenum                  swizzle_a;
	GLsizei                 bits_per_texel;
};

static const DDS_FORMAT_GL_INFO gl_info_table[] =
{
	// format,              type,               internalFormat,     swizzle_r,      swizzle_g,      swizzle_b,      swizzle_a
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    0 },        // DDS_FORMAT_UNKNOWN
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    0 },        // DDS_FORMAT_R32G32B32A32_TYPELESS
	{ GL_RGBA,              GL_FLOAT,           GL_RGBA32F,         GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   128 },      // DDS_FORMAT_R32G32B32A32_FLOAT
	{ GL_RGBA_INTEGER,      GL_UNSIGNED_INT,    GL_RGBA32UI,        GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   128 },      // DDS_FORMAT_R32G32B32A32_UINT
	{ GL_RGBA_INTEGER,      GL_INT,             GL_RGBA32I,         GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   128 },      // DDS_FORMAT_R32G32B32A32_SINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    96 },       // DDS_FORMAT_R32G32B32_TYPELESS
	{ GL_RGB,               GL_FLOAT,           GL_RGB32F,          GL_RED,         GL_GREEN,       GL_BLUE,        GL_ONE,     96 },       // DDS_FORMAT_R32G32B32_FLOAT
	{ GL_RGB_INTEGER,       GL_UNSIGNED_INT,    GL_RGB32UI,         GL_RED,         GL_GREEN,       GL_BLUE,        GL_ONE,     96 },       // DDS_FORMAT_R32G32B32_UINT
	{ GL_RGB_INTEGER,       GL_INT,             GL_RGB32I,          GL_RED,         GL_GREEN,       GL_BLUE,        GL_ONE,     96 },       // DDS_FORMAT_R32G32B32_SINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    64 },       // DDS_FORMAT_R16G16B16A16_TYPELESS
	{ GL_RGBA,              GL_HALF_FLOAT,      GL_RGBA16F,         GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   64 },       // DDS_FORMAT_R16G16B16A16_FLOAT
	{ GL_RGBA,              GL_UNSIGNED_SHORT,  GL_RGBA16,          GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   64 },       // DDS_FORMAT_R16G16B16A16_UNORM
	{ GL_RGBA_INTEGER,      GL_UNSIGNED_SHORT,  GL_RGBA16UI,        GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   64 },       // DDS_FORMAT_R16G16B16A16_UINT
	{ GL_RGBA,              GL_SHORT,           GL_RGBA16_SNORM,    GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   64 },       // DDS_FORMAT_R16G16B16A16_SNORM
	{ GL_RGBA_INTEGER,      GL_SHORT,           GL_RGBA16I,         GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   64 },       // DDS_FORMAT_R16G16B16A16_SINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    64 },       // DDS_FORMAT_R32G32_TYPELESS
	{ GL_RG,                GL_FLOAT,           GL_RG32F,           GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     64 },       // DDS_FORMAT_R32G32_FLOAT
	{ GL_RG_INTEGER,        GL_UNSIGNED_INT,    GL_RG32UI,          GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     64 },       // DDS_FORMAT_R32G32_UINT
	{ GL_RG_INTEGER,        GL_INT,             GL_RG32I,           GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     64 },       // DDS_FORMAT_R32G32_SINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    64 },       // DDS_FORMAT_R32G8X24_TYPELESS
	{ GL_DEPTH_STENCIL,     GL_FLOAT_32_UNSIGNED_INT_24_8_REV,  GL_DEPTH32F_STENCIL8, GL_NONE, GL_NONE, GL_NONE,    GL_NONE,    64 },       // DDS_FORMAT_D32_FLOAT_S8X24_UINT (THIS MAY NOT BE RIGHT)
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    64 },       // DDS_FORMAT_R32_FLOAT_X8X24_TYPELESS
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    64 },      // DDS_FORMAT_X32_TYPELESS_G8X24_UINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    32 },      // DDS_FORMAT_R10G10B10A2_TYPELESS
	{ GL_RGBA,              GL_UNSIGNED_INT,    GL_RGB10_A2,        GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   32 },      // DDS_FORMAT_R10G10B10A2_UNORM
	{ GL_RGBA_INTEGER,      GL_UNSIGNED_INT,    GL_RGB10_A2UI,      GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   32 },      // DDS_FORMAT_R10G10B10A2_UINT
	{ GL_RGB,               GL_UNSIGNED_INT,    GL_R11F_G11F_B10F,  GL_RED,         GL_GREEN,       GL_BLUE,        GL_ONE,     32 },      // DDS_FORMAT_R11G11B10_FLOAT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    32 },      // DDS_FORMAT_R8G8B8A8_TYPELESS
	{ GL_RGBA,              GL_UNSIGNED_BYTE,   GL_RGBA8,           GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   32 },      // DDS_FORMAT_R8G8B8A8_UNORM
	{ GL_RGBA,              GL_UNSIGNED_BYTE,   GL_SRGB8_ALPHA8,    GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   32 },      // DDS_FORMAT_R8G8B8A8_UNORM_SRGB
	{ GL_RGBA_INTEGER,      GL_UNSIGNED_BYTE,   GL_RGBA8UI,         GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   32 },      // DDS_FORMAT_R8G8B8A8_UINT
	{ GL_RGBA,              GL_BYTE,            GL_RGBA8_SNORM,     GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   32 },      // DDS_FORMAT_R8G8B8A8_SNORM
	{ GL_RGBA_INTEGER,      GL_BYTE,            GL_RGBA8I,          GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA,   32 },      // DDS_FORMAT_R8G8B8A8_SINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    32 },      // DDS_FORMAT_R16G16_TYPELESS
	{ GL_RG,                GL_HALF_FLOAT,      GL_RG16F,           GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     32 },      // DDS_FORMAT_R16G16_FLOAT
	{ GL_RG,                GL_UNSIGNED_SHORT,  GL_RG16,            GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     32 },      // DDS_FORMAT_R16G16_UNORM
	{ GL_RG_INTEGER,        GL_UNSIGNED_SHORT,  GL_RG16UI,          GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     32 },      // DDS_FORMAT_R16G16_UINT
	{ GL_RG,                GL_SHORT,           GL_RG16_SNORM,      GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     32 },      // DDS_FORMAT_R16G16_SNORM
	{ GL_RG_INTEGER,        GL_SHORT,           GL_RG16I,           GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     32 },      // DDS_FORMAT_R16G16_SINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    32 },      // DDS_FORMAT_R32_TYPELESS
	{ GL_DEPTH_COMPONENT,   GL_FLOAT,           GL_DEPTH_COMPONENT32F,  GL_RED,     GL_ZERO,        GL_ZERO,        GL_ZERO,    32 },      // DDS_FORMAT_D32_FLOAT
	{ GL_RED,               GL_FLOAT,           GL_R32F,            GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     32 },      // DDS_FORMAT_R32_FLOAT
	{ GL_RED_INTEGER,       GL_UNSIGNED_INT,    GL_R32UI,           GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     32 },      // DDS_FORMAT_R32_UINT
	{ GL_RED_INTEGER,       GL_INT,             GL_R32I,            GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     32 },      // DDS_FORMAT_R32_SINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    32 },      // DDS_FORMAT_R24G8_TYPELESS
	{ GL_DEPTH_STENCIL,     GL_UNSIGNED_INT,    GL_DEPTH24_STENCIL8, GL_RED,        GL_GREEN,       GL_ZERO,        GL_ZERO,    32 },      // DDS_FORMAT_D24_UNORM_S8_UINT (MAY NOT BE CORRECT)
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    32 },      // DDS_FORMAT_R24_UNORM_X8_TYPELESS
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    32 },      // DDS_FORMAT_X24_TYPELESS_G8_UINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    16 },      // DDS_FORMAT_R8G8_TYPELESS
	{ GL_RG,                GL_UNSIGNED_BYTE,   GL_RG8,             GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     16 },      // DDS_FORMAT_R8G8_UNORM
	{ GL_RG_INTEGER,        GL_UNSIGNED_BYTE,   GL_RG8UI,           GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     16 },      // DDS_FORMAT_R8G8_UINT
	{ GL_RG,                GL_BYTE,            GL_RG8_SNORM,       GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     16 },      // DDS_FORMAT_R8G8_SNORM
	{ GL_RG_INTEGER,        GL_BYTE,            GL_RG8I,            GL_RED,         GL_GREEN,       GL_ZERO,        GL_ONE,     16 },      // DDS_FORMAT_R8G8_SINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    16 },      // DDS_FORMAT_R16_TYPELESS
	{ GL_RED,               GL_HALF_FLOAT,      GL_R16F,            GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     16 },      // DDS_FORMAT_R16_FLOAT
	{ GL_DEPTH_COMPONENT,   GL_HALF_FLOAT,      GL_DEPTH_COMPONENT16, GL_RED,       GL_ZERO,        GL_ZERO,        GL_ZERO,    16 },      // DDS_FORMAT_D16_UNORM
	{ GL_RED,               GL_UNSIGNED_SHORT,  GL_R16,             GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     16 },      // DDS_FORMAT_R16_UNORM
	{ GL_RED_INTEGER,       GL_UNSIGNED_SHORT,  GL_R16UI,           GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     16 },      // DDS_FORMAT_R16_UINT
	{ GL_RED,               GL_SHORT,           GL_R16_SNORM,       GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     16 },      // DDS_FORMAT_R16_SNORM
	{ GL_RED_INTEGER,       GL_SHORT,           GL_R16I,            GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     16 },      // DDS_FORMAT_R16_SINT
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    8 },       // DDS_FORMAT_R8_TYPELESS
	{ GL_RED,               GL_UNSIGNED_BYTE,   GL_R8,              GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     8 },       // DDS_FORMAT_R8_UNORM
	{ GL_RED_INTEGER,       GL_UNSIGNED_BYTE,   GL_R8UI,            GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     8 },       // DDS_FORMAT_R8_UINT
	{ GL_RED,               GL_BYTE,            GL_R8_SNORM,        GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     8 },       // DDS_FORMAT_R8_SNORM
	{ GL_RED_INTEGER,       GL_BYTE,            GL_R8I,             GL_RED,         GL_ZERO,        GL_ZERO,        GL_ONE,     8 },       // DDS_FORMAT_R8_SINT
	{ GL_RED,               GL_BYTE,            GL_R8,              GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_RED,     8 },       // DDS_FORMAT_A8_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    0 },       // DDS_FORMAT_R1_UNORM
	{ GL_RGB,               GL_UNSIGNED_SHORT,  GL_RGB9_E5,         GL_RED,         GL_GREEN,       GL_BLUE,        GL_ONE,     16 },      // DDS_FORMAT_R9G9B9E5_SHAREDEXP
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    16 },      // DDS_FORMAT_R8G8_B8G8_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO,    16 },      // DDS_FORMAT_G8R8_G8B8_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC1_TYPELESS
#if defined GL_EXT_texture_compression_s3tc
	{ GL_COMPRESSED_RGB_S3TC_DXT1_EXT, GL_NONE, GL_COMPRESSED_RGB_S3TC_DXT1_EXT, GL_RED, GL_GREEN,  GL_BLUE,        GL_ONE },      // DDS_FORMAT_BC1_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC1_UNORM_SRGB
#else
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC1_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC1_UNORM_SRGB
#endif
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC2_TYPELESS
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC2_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC2_UNORM_SRGB
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC3_TYPELESS
#if defined GL_EXT_texture_compression_s3tc
																																	//    { GL_COMPRESSED_RGB_S3TC_DXT3_EXT,  GL_NONE, GL_COMPRESSED_RGB_S3TC_DXT3_EXT, GL_ZERO, GL_ZERO, GL_ZERO,        GL_ZERO             },      // DDS_FORMAT_BC3_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC3_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC3_UNORM_SRGB
#else
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC3_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC3_UNORM_SRGB
#endif
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC4_TYPELESS
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC4_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC4_SNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC5_TYPELESS
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC5_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC5_SNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_B5G6R5_UNORM
	{ GL_RGBA,              GL_UNSIGNED_SHORT,  GL_RGB5_A1,         GL_RED,         GL_GREEN,       GL_BLUE,        GL_ALPHA },      // DDS_FORMAT_B5G5R5A1_UNORM
	{ GL_RGBA,              GL_UNSIGNED_BYTE,   GL_RGBA8,           GL_BLUE,        GL_GREEN,       GL_RED,         GL_ALPHA },      // DDS_FORMAT_B8G8R8A8_UNORM
	{ GL_RGBA,              GL_UNSIGNED_BYTE,   GL_RGBA8,           GL_RED,         GL_GREEN,       GL_BLUE,        GL_ONE },      // DDS_FORMAT_B8G8R8X8_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_R10G10B10_XR_BIAS_A2_UNORM
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_B8G8R8A8_TYPELESS
	{ GL_RGBA,              GL_UNSIGNED_BYTE,   GL_SRGB8_ALPHA8,    GL_BLUE,        GL_GREEN,       GL_RED,         GL_ALPHA },      // DDS_FORMAT_B8G8R8A8_UNORM_SRGB
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_B8G8R8X8_TYPELESS
	{ GL_RGBA,              GL_UNSIGNED_BYTE,   GL_SRGB8_ALPHA8,    GL_BLUE,        GL_GREEN,       GL_RED,         GL_ONE },      // DDS_FORMAT_B8G8R8X8_UNORM_SRGB
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC6H_TYPELESS
	{ GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB, GL_NONE, GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB, GL_RED, GL_GREEN, GL_BLUE,     GL_ONE },      // DDS_FORMAT_BC6H_UF16
	{ GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB, GL_NONE, GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB, GL_RED, GL_GREEN, GL_BLUE, GL_ONE },   // DDS_FORMAT_BC6H_SF16
	{ GL_NONE,              GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_BC7_TYPELESS
	{ GL_COMPRESSED_RGBA_BPTC_UNORM_ARB, GL_NONE, GL_COMPRESSED_RGBA_BPTC_UNORM_ARB, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA },      // DDS_FORMAT_BC7_UNORM
	{ GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB, GL_NONE, GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB, GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA }, // DDS_FORMAT_BC7_UNORM_SRGB
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_AYUV
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_Y410
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_Y416
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_NV12
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_P010
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_P016
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_420_OPAQUE
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_YUY2
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_Y210
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_Y216
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_NV11
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_AI44
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_IA44
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_P8
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_A8P8
	{ GL_NONE,          GL_NONE,            GL_NONE,            GL_ZERO,        GL_ZERO,        GL_ZERO,        GL_ZERO },      // DDS_FORMAT_B4G4R4A4_UNORM
};


#endif // !VDDS_H

