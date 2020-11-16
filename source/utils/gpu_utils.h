/*
 * This file is part of vitaGL
 * Copyright 2017, 2018, 2019, 2020 Rinnegatamante
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * gpu_utils.h:
 * Header file for the GPU utilities exposed by gpu_utils.c
 */

#ifndef _GPU_UTILS_H_
#define _GPU_UTILS_H_

#include "mem_utils.h"

// Align a value to the requested alignment
#define ALIGN(x, a) (((x) + ((a)-1)) & ~((a)-1))

// Texture object struct
typedef struct texture {
	SceGxmTexture gxm_tex;
	void *data;
	vglMemType mtype;
	SceUID palette_UID;
	SceUID depth_UID;
	uint8_t used;
	uint8_t valid;
	uint32_t type;
	void (*write_cb)(void *, uint32_t);
	SceGxmTextureFilter min_filter;
	SceGxmTextureFilter mag_filter;
	SceGxmTextureAddrMode u_mode;
	SceGxmTextureAddrMode v_mode;
	SceGxmTextureMipFilter mip_filter;
	uint32_t lod_bias;
} texture;

// Palette object struct
typedef struct palette {
	void *data;
	vglMemType type;
} palette;

// Utility Function.
uint32_t nearest_po2(uint32_t val); 
// Swizzle and copy texture region.
void swizzle_compressed_texture_region(void *dst, const void *src, int tex_width, int tex_height, int region_x, int region_y, int region_width, int region_height, int isdxt5, int ispvrt2bpp);

// Alloc a generic memblock into sceGxm mapped memory
void *gpu_alloc_mapped(size_t size, vglMemType *type);

// Alloc into sceGxm mapped memory a vertex USSE memblock
void *gpu_vertex_usse_alloc_mapped(size_t size, unsigned int *usse_offset);

// Dealloc from sceGxm mapped memory a vertex USSE memblock
void gpu_vertex_usse_free_mapped(void *addr);

// Alloc into sceGxm mapped memory a fragment USSE memblock
void *gpu_fragment_usse_alloc_mapped(size_t size, unsigned int *usse_offset);

// Dealloc from sceGxm mapped memory a fragment USSE memblock
void gpu_fragment_usse_free_mapped(void *addr);

// Reserve a memory space from vitaGL mempool
void *gpu_pool_malloc(unsigned int size);

// Reserve an aligned memory space from vitaGL mempool
void *gpu_pool_memalign(unsigned int size, unsigned int alignment);

// Returns available free space on vitaGL mempool
unsigned int gpu_pool_free_space();

// Resets vitaGL mempool
void gpu_pool_reset();

// Alloc vitaGL mempool
void gpu_pool_init(uint32_t temp_pool_size);

// Calculate bpp for a requested texture format
int tex_format_to_bytespp(SceGxmTextureFormat format);

// Alloc a texture
void gpu_alloc_texture(uint32_t w, uint32_t h, SceGxmTextureFormat format, const void *data, texture *tex, uint8_t src_bpp, uint32_t (*read_cb)(void *), void (*write_cb)(void *, uint32_t), uint8_t fast_store);

// Alloc a compresseed texture
void gpu_alloc_compressed_texture(uint32_t mipLevel, uint32_t w, uint32_t h, SceGxmTextureFormat format, uint32_t image_size, const void *data, texture *tex, uint8_t src_bpp, uint32_t (*read_cb)(void *));

// Dealloc a texture
void gpu_free_texture(texture *tex);

// Alloc a palette
palette *gpu_alloc_palette(const void *data, uint32_t w, uint32_t bpe);

// Dealloc a palette
void gpu_free_palette(palette *pal);

// Generate mipmaps for a given texture
void gpu_alloc_mipmaps(int level, texture *tex);

// Get the size of a mipchain with the last mip width and height
int gpu_get_mipchain_size(int level, int width, int height, SceGxmTextureFormat format);

// Get the offset of a specified mip level, of a given width and height.
int gpu_get_mip_offset(int level, int width, int height, SceGxmTextureFormat format);

// Get dimensions of a mip level, given top level dimensions.
void gpu_get_mip_size(int level, int width, int height, int *mip_width, int *mip_height);

#endif
