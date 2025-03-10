// taken from https://github.com/richgel999/bc7enc_rdo, where it's put into
// the Public Domain (or alternatively MIT License)
// I also adjusted some names to better match the Microsoft documentation
// https://learn.microsoft.com/en-us/windows/win32/direct3ddds/dds-header
// File: dds_defs.h
// DX9/10 .DDS file header definitions.
#pragma once

#include <stdint.h>

#define PIXEL_FMT_FOURCC(a, b, c, d) ((a) | ((b) << 8U) | ((c) << 16U) | ((d) << 24U))

enum pixel_format
{
	PIXEL_FMT_INVALID = 0,

	PIXEL_FMT_DXT1 = PIXEL_FMT_FOURCC('D', 'X', 'T', '1'), // BC1
	PIXEL_FMT_DXT2 = PIXEL_FMT_FOURCC('D', 'X', 'T', '2'), // BC2 with premultiplied alpha
	PIXEL_FMT_DXT3 = PIXEL_FMT_FOURCC('D', 'X', 'T', '3'), // BC2
	PIXEL_FMT_DXT4 = PIXEL_FMT_FOURCC('D', 'X', 'T', '4'), // BC3 with premultiplied alpha
	PIXEL_FMT_DXT5 = PIXEL_FMT_FOURCC('D', 'X', 'T', '5'), // BC3
	PIXEL_FMT_3DC = PIXEL_FMT_FOURCC('A', 'T', 'I', '2'), // DXN_YX - BC5 with swapped channels
	PIXEL_FMT_DXN = PIXEL_FMT_FOURCC('A', '2', 'X', 'Y'), // DXN_XY - BC5
	PIXEL_FMT_BC5S = PIXEL_FMT_FOURCC('B', 'C', '5', 'S'), // BC5 SNORM
	PIXEL_FMT_BC5U = PIXEL_FMT_FOURCC('B', 'C', '5', 'U'), // BC5 UNORM
	PIXEL_FMT_DXT5A = PIXEL_FMT_FOURCC('A', 'T', 'I', '1'), // BC4 aka ATI1N, http://developer.amd.com/media/gpu_assets/Radeon_X1x00_Programming_Guide.pdf
	PIXEL_FMT_BC4U = PIXEL_FMT_FOURCC('B', 'C', '4', 'U'), // BC4 UNORM
	PIXEL_FMT_BC4S = PIXEL_FMT_FOURCC('B', 'C', '4', 'S'), // BC4 SNORM

	// Non-standard formats (some of these are supported by ATI's Compressonator)
	PIXEL_FMT_DXT5_CCxY = PIXEL_FMT_FOURCC('C', 'C', 'x', 'Y'),
	PIXEL_FMT_DXT5_xGxR = PIXEL_FMT_FOURCC('x', 'G', 'x', 'R'),
	PIXEL_FMT_DXT5_xGBR = PIXEL_FMT_FOURCC('x', 'G', 'B', 'R'),
	PIXEL_FMT_DXT5_RXGB = PIXEL_FMT_FOURCC('R', 'X', 'G', 'B'), // used for normalmaps in Doom3, same as xGBR (misnamed)
	PIXEL_FMT_DXT5_AGBR = PIXEL_FMT_FOURCC('A', 'G', 'B', 'R'),

	PIXEL_FMT_DXT1A = PIXEL_FMT_FOURCC('D', 'X', '1', 'A'), // BC1 with alpha?
	PIXEL_FMT_ETC1 = PIXEL_FMT_FOURCC('E', 'T', 'C', '1'),

	PIXEL_FMT_R8G8B8 = PIXEL_FMT_FOURCC('R', 'G', 'B', 'x'),
	PIXEL_FMT_L8 = PIXEL_FMT_FOURCC('L', 'x', 'x', 'x'),
	PIXEL_FMT_A8 = PIXEL_FMT_FOURCC('x', 'x', 'x', 'A'),
	PIXEL_FMT_A8L8 = PIXEL_FMT_FOURCC('L', 'x', 'x', 'A'),
	PIXEL_FMT_A8R8G8B8 = PIXEL_FMT_FOURCC('R', 'G', 'B', 'A'),
};

const uint32_t cDDSMaxImageDimensions = 8192U;

// Total size of header is sizeof(uint32)+cDDSSizeofDDSurfaceDesc2;
const uint32_t cDDSSizeofDDSurfaceDesc2 = 124;

const uint32_t DX10fourcc = PIXEL_FMT_FOURCC('D', 'X', '1', '0');

// "DDS "
const uint32_t cDDSFileSignature = 0x20534444;

struct DDS_PIXELFORMAT
{
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwFourCC;
	uint32_t dwRGBBitCount;     // ATI compressonator will place a FOURCC code here for swizzled/cooked DXTn formats
	uint32_t dwRBitMask;
	uint32_t dwGBitMask;
	uint32_t dwBBitMask;
	uint32_t dwRGBAlphaBitMask;
};

struct DDS_HEADER
{
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwHeight;
	uint32_t dwWidth;
	union
	{
		int32_t lPitch;
		uint32_t dwLinearSize;
	};
	uint32_t dwDepth;
	uint32_t dwMipMapCount;
	uint32_t dwReserved1[11];
	DDS_PIXELFORMAT ddpfPixelFormat;
	uint32_t dwCaps;
	uint32_t dwCaps2;
	uint32_t dwCaps3;
	uint32_t dwCaps4;
	uint32_t dwReserved2;
};

const uint32_t DDSD_CAPS = 0x00000001;
const uint32_t DDSD_HEIGHT = 0x00000002;
const uint32_t DDSD_WIDTH = 0x00000004;
const uint32_t DDSD_PITCH = 0x00000008;

const uint32_t DDSD_BACKBUFFERCOUNT = 0x00000020;
const uint32_t DDSD_ZBUFFERBITDEPTH = 0x00000040;
const uint32_t DDSD_ALPHABITDEPTH = 0x00000080;

const uint32_t DDSD_LPSURFACE = 0x00000800;

const uint32_t DDSD_PIXELFORMAT = 0x00001000;
const uint32_t DDSD_CKDESTOVERLAY = 0x00002000;
const uint32_t DDSD_CKDESTBLT = 0x00004000;
const uint32_t DDSD_CKSRCOVERLAY = 0x00008000;

const uint32_t DDSD_CKSRCBLT = 0x00010000;
const uint32_t DDSD_MIPMAPCOUNT = 0x00020000;
const uint32_t DDSD_REFRESHRATE = 0x00040000;
const uint32_t DDSD_LINEARSIZE = 0x00080000;

const uint32_t DDSD_TEXTURESTAGE = 0x00100000;
const uint32_t DDSD_FVF = 0x00200000;
const uint32_t DDSD_SRCVBHANDLE = 0x00400000;
const uint32_t DDSD_DEPTH = 0x00800000;

const uint32_t DDSD_ALL = 0x00fff9ee;

const uint32_t DDPF_ALPHAPIXELS = 0x00000001;
const uint32_t DDPF_ALPHA = 0x00000002;
const uint32_t DDPF_FOURCC = 0x00000004;
const uint32_t DDPF_PALETTEINDEXED8 = 0x00000020;
const uint32_t DDPF_RGB = 0x00000040;
const uint32_t DDPF_LUMINANCE = 0x00020000;

const uint32_t DDSCAPS_COMPLEX = 0x00000008;
const uint32_t DDSCAPS_TEXTURE = 0x00001000;
const uint32_t DDSCAPS_MIPMAP = 0x00400000;

const uint32_t DDSCAPS2_CUBEMAP = 0x00000200;
const uint32_t DDSCAPS2_CUBEMAP_POSITIVEX = 0x00000400;
const uint32_t DDSCAPS2_CUBEMAP_NEGATIVEX = 0x00000800;

const uint32_t DDSCAPS2_CUBEMAP_POSITIVEY = 0x00001000;
const uint32_t DDSCAPS2_CUBEMAP_NEGATIVEY = 0x00002000;
const uint32_t DDSCAPS2_CUBEMAP_POSITIVEZ = 0x00004000;
const uint32_t DDSCAPS2_CUBEMAP_NEGATIVEZ = 0x00008000;

const uint32_t DDSCAPS2_VOLUME = 0x00200000;

enum {
	DDS_DX10MISC2_ALPHA_UNKNOWN       = 0,
	DDS_DX10MISC2_ALPHA_STRAIGHT      = 1,
	DDS_DX10MISC2_ALPHA_PREMULTIPLIED = 2,
	DDS_DX10MISC2_ALPHA_OPAQUE        = 3,
	DDS_DX10MISC2_ALPHA_CUSTOM        = 4, // alpha is 4th channel, not really alpha
};

typedef enum DXGI_FORMAT 
{
	DXGI_FORMAT_UNKNOWN = 0,
	DXGI_FORMAT_R32G32B32A32_TYPELESS = 1,
	DXGI_FORMAT_R32G32B32A32_FLOAT = 2,
	DXGI_FORMAT_R32G32B32A32_UINT = 3,
	DXGI_FORMAT_R32G32B32A32_SINT = 4,
	DXGI_FORMAT_R32G32B32_TYPELESS = 5,
	DXGI_FORMAT_R32G32B32_FLOAT = 6,
	DXGI_FORMAT_R32G32B32_UINT = 7,
	DXGI_FORMAT_R32G32B32_SINT = 8,
	DXGI_FORMAT_R16G16B16A16_TYPELESS = 9,
	DXGI_FORMAT_R16G16B16A16_FLOAT = 10,
	DXGI_FORMAT_R16G16B16A16_UNORM = 11,
	DXGI_FORMAT_R16G16B16A16_UINT = 12,
	DXGI_FORMAT_R16G16B16A16_SNORM = 13,
	DXGI_FORMAT_R16G16B16A16_SINT = 14,
	DXGI_FORMAT_R32G32_TYPELESS = 15,
	DXGI_FORMAT_R32G32_FLOAT = 16,
	DXGI_FORMAT_R32G32_UINT = 17,
	DXGI_FORMAT_R32G32_SINT = 18,
	DXGI_FORMAT_R32G8X24_TYPELESS = 19,
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT = 20,
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
	DXGI_FORMAT_R10G10B10A2_TYPELESS = 23,
	DXGI_FORMAT_R10G10B10A2_UNORM = 24,
	DXGI_FORMAT_R10G10B10A2_UINT = 25,
	DXGI_FORMAT_R11G11B10_FLOAT = 26,
	DXGI_FORMAT_R8G8B8A8_TYPELESS = 27,
	DXGI_FORMAT_R8G8B8A8_UNORM = 28,
	DXGI_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
	DXGI_FORMAT_R8G8B8A8_UINT = 30,
	DXGI_FORMAT_R8G8B8A8_SNORM = 31,
	DXGI_FORMAT_R8G8B8A8_SINT = 32,
	DXGI_FORMAT_R16G16_TYPELESS = 33,
	DXGI_FORMAT_R16G16_FLOAT = 34,
	DXGI_FORMAT_R16G16_UNORM = 35,
	DXGI_FORMAT_R16G16_UINT = 36,
	DXGI_FORMAT_R16G16_SNORM = 37,
	DXGI_FORMAT_R16G16_SINT = 38,
	DXGI_FORMAT_R32_TYPELESS = 39,
	DXGI_FORMAT_D32_FLOAT = 40,
	DXGI_FORMAT_R32_FLOAT = 41,
	DXGI_FORMAT_R32_UINT = 42,
	DXGI_FORMAT_R32_SINT = 43,
	DXGI_FORMAT_R24G8_TYPELESS = 44,
	DXGI_FORMAT_D24_UNORM_S8_UINT = 45,
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS = 46,
	DXGI_FORMAT_X24_TYPELESS_G8_UINT = 47,
	DXGI_FORMAT_R8G8_TYPELESS = 48,
	DXGI_FORMAT_R8G8_UNORM = 49,
	DXGI_FORMAT_R8G8_UINT = 50,
	DXGI_FORMAT_R8G8_SNORM = 51,
	DXGI_FORMAT_R8G8_SINT = 52,
	DXGI_FORMAT_R16_TYPELESS = 53,
	DXGI_FORMAT_R16_FLOAT = 54,
	DXGI_FORMAT_D16_UNORM = 55,
	DXGI_FORMAT_R16_UNORM = 56,
	DXGI_FORMAT_R16_UINT = 57,
	DXGI_FORMAT_R16_SNORM = 58,
	DXGI_FORMAT_R16_SINT = 59,
	DXGI_FORMAT_R8_TYPELESS = 60,
	DXGI_FORMAT_R8_UNORM = 61,
	DXGI_FORMAT_R8_UINT = 62,
	DXGI_FORMAT_R8_SNORM = 63,
	DXGI_FORMAT_R8_SINT = 64,
	DXGI_FORMAT_A8_UNORM = 65,
	DXGI_FORMAT_R1_UNORM = 66,
	DXGI_FORMAT_R9G9B9E5_SHAREDEXP = 67,
	DXGI_FORMAT_R8G8_B8G8_UNORM = 68,
	DXGI_FORMAT_G8R8_G8B8_UNORM = 69,
	DXGI_FORMAT_BC1_TYPELESS = 70,
	DXGI_FORMAT_BC1_UNORM = 71,
	DXGI_FORMAT_BC1_UNORM_SRGB = 72,
	DXGI_FORMAT_BC2_TYPELESS = 73,
	DXGI_FORMAT_BC2_UNORM = 74,
	DXGI_FORMAT_BC2_UNORM_SRGB = 75,
	DXGI_FORMAT_BC3_TYPELESS = 76,
	DXGI_FORMAT_BC3_UNORM = 77,
	DXGI_FORMAT_BC3_UNORM_SRGB = 78,
	DXGI_FORMAT_BC4_TYPELESS = 79,
	DXGI_FORMAT_BC4_UNORM = 80,
	DXGI_FORMAT_BC4_SNORM = 81,
	DXGI_FORMAT_BC5_TYPELESS = 82,
	DXGI_FORMAT_BC5_UNORM = 83,
	DXGI_FORMAT_BC5_SNORM = 84,
	DXGI_FORMAT_B5G6R5_UNORM = 85,
	DXGI_FORMAT_B5G5R5A1_UNORM = 86,
	DXGI_FORMAT_B8G8R8A8_UNORM = 87,
	DXGI_FORMAT_B8G8R8X8_UNORM = 88,
	DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
	DXGI_FORMAT_B8G8R8A8_TYPELESS = 90,
	DXGI_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
	DXGI_FORMAT_B8G8R8X8_TYPELESS = 92,
	DXGI_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
	DXGI_FORMAT_BC6H_TYPELESS = 94,
	DXGI_FORMAT_BC6H_UF16 = 95,
	DXGI_FORMAT_BC6H_SF16 = 96,
	DXGI_FORMAT_BC7_TYPELESS = 97,
	DXGI_FORMAT_BC7_UNORM = 98,
	DXGI_FORMAT_BC7_UNORM_SRGB = 99,
	DXGI_FORMAT_AYUV = 100,
	DXGI_FORMAT_Y410 = 101,
	DXGI_FORMAT_Y416 = 102,
	DXGI_FORMAT_NV12 = 103,
	DXGI_FORMAT_P010 = 104,
	DXGI_FORMAT_P016 = 105,
	DXGI_FORMAT_420_OPAQUE = 106,
	DXGI_FORMAT_YUY2 = 107,
	DXGI_FORMAT_Y210 = 108,
	DXGI_FORMAT_Y216 = 109,
	DXGI_FORMAT_NV11 = 110,
	DXGI_FORMAT_AI44 = 111,
	DXGI_FORMAT_IA44 = 112,
	DXGI_FORMAT_P8 = 113,
	DXGI_FORMAT_A8P8 = 114,
	DXGI_FORMAT_B4G4R4A4_UNORM = 115,
	DXGI_FORMAT_P208 = 130,
	DXGI_FORMAT_V208 = 131,
	DXGI_FORMAT_V408 = 132,
	DXGI_FORMAT_FORCE_UINT = 0xffffffff
} DXGI_FORMAT;

enum D3D10_RESOURCE_DIMENSION 
{
	D3D10_RESOURCE_DIMENSION_UNKNOWN = 0,
	D3D10_RESOURCE_DIMENSION_BUFFER = 1,
	D3D10_RESOURCE_DIMENSION_TEXTURE1D = 2,
	D3D10_RESOURCE_DIMENSION_TEXTURE2D = 3,
	D3D10_RESOURCE_DIMENSION_TEXTURE3D = 4
};

struct DDS_HEADER_DXT10
{
	DXGI_FORMAT              dxgiFormat;
	D3D10_RESOURCE_DIMENSION resourceDimension;
	uint32_t                 miscFlag;
	uint32_t                 arraySize;
	uint32_t                 miscFlags2;
};

