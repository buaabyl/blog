/* vim: set fileencoding=utf-8:
 *
 *                   GNU GENERAL PUBLIC LICENSE
 *                       Version 2, June 1991
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
 * @ref ug585: 6.3.2 BootROM Header
 * @ref fsbl: image_mover.h, image_mover.c, fsbl.h
 *
 * Why I need another bootrom creator or decoder?
 * The main reason is `just for fun`.
 * Because I use GCC+Makefile directly,
 * I don't need xilinx SDK or petalinux toolchain.
 * Hope this utils can replace partitions data in the easy way.
 *
 * This utils will implement
 * - parser for BOOT.bin
 * - demux BOOT.bin to seperate bin files
 * - creator to combine all seperate back to BOOT.bin
 *
 *
 * 2018.04.07   try to decode BOOT.bin file
 *
 */
#ifndef BOOTROM_H_8590DB10_F7ED_50C0_1AD2_067467273D9F_INCLUDED_
#define BOOTROM_H_8590DB10_F7ED_50C0_1AD2_067467273D9F_INCLUDED_


#define SZ_BOOTROM_HEADER   0x900
#define EFUSE_KEY_ENCRYPTED 0xA5C3C5A3
#define RAM_KEY_ENCRYPTED   0x3A5C3C5A

#define MAX_PARTITION_NUMBER        0xE
#define IMAGE_HEADER_SIZE           64
#define IMAGE_HEADER_TABLE_SIZE     64
#define TOTAL_PARTITION_HEADER_SIZE (MAX_PARTITION_NUMBER * IMAGE_HEADER_SIZE)
#define TOTAL_IMAGE_HEADER_SIZE     (MAX_PARTITION_NUMBER * IMAGE_HEADER_SIZE)
#define TOTAL_HEADER_SIZE           (IMAGE_HEADER_TABLE_SIZE + \
                                    TOTAL_IMAGE_HEADER_SIZE + \
                                    TOTAL_PARTITION_HEADER_SIZE + 64)
#define RSA_SIGNATURE_SIZE          0x6C0


//
// `LE` means little endian
//
typedef struct {
    uint32_t interrupt_table[8];    // 'h000 - 'h01F
    uint32_t qspi_width;            // 'h020: magic 0xAA995566 (LE)
    uint32_t identification;        // 'h024: magic string 'XLNX' (LE)
    uint32_t encryption_status;     // 'h028:
                                    //  - 0xA5C3C5A3(LE): eFUSE key
                                    //  - 0x3A5C3C5A(LE): battery-backed RAM key
                                    //  - other: non-encrypted
    /* fsbl or application */
    uint32_t source_version;        // 'h02C: bootrom ignored it
    uint32_t source_address;        // 'h030: algined 64bytes, from the begin.
    uint32_t bytes_length;          // 'h034: bytes count of fsbl
    uint32_t load_address;          // 'h038 
    uint32_t start_address;         // 'h03C
    uint32_t total_image_length;    // 'h040

    uint32_t qspi_config;           // 'h044: magic 0x01 (LE)
    uint32_t header_checksum;       // 'h048: ~sum(0x20, 0x44)

    uint32_t user_defined[19];      // 'h04C - 'h097, bootrom ignored it
    uint32_t image_hdr_offset;      // 'h098, image header offset
    uint32_t image_phdr_offset;     // 'h09C, image partition header offset
    uint32_t registers_init[512];   // 'h0A0 - 'h89F: two uint32_t/pair
    uint32_t image_header[24];      // 'h8A0 - 'h8FF

    // 'h900: fsbl or user code
}bootrom_hdr_t;


//partition_attribute
#define ATTRIBUTE_IMAGE_TYPE_MASK		0x000F0	/* Destination Device type */
#define ATTRIBUTE_PS_IMAGE_MASK			0x00010	/* Code partition */
#define ATTRIBUTE_PL_IMAGE_MASK			0x00020	/* Bit stream partition */
#define ATTRIBUTE_CHECKSUM_TYPE_MASK	0x07000	/* Checksum Type */
#define ATTRIBUTE_RSA_PRESENT_MASK		0x08000	/* RSA Signature Present */
#define ATTRIBUTE_PARTITION_OWNER_MASK	0x30000	/* Partition Owner */

#define ATTRIBUTE_PARTITION_OWNER_FSBL	0x00000	/* FSBL Partition Owner */

// start from image_phdr_offset, 
typedef struct {
    uint32_t image_word_length;     // 'h00, partition image length (of 32bit)
    uint32_t data_word_length;      // 'h04, encrypted data length (when encrypted)
    uint32_t partition_word_length; // 'h08, partition total length
    uint32_t load_address;          // 'h0C
    uint32_t start_address;         // 'h10
    uint32_t partition_start;       // 'h14
    uint32_t partition_attribute;   // 'h18
    uint32_t section_count;         // 'h1C
    uint32_t md5sum_offset;         // 'h20, from bootrom begin (32bit offset)
    uint32_t padding0[1];
    uint32_t ac_offset;             // 'h28 
    uint32_t padding1[4];
    uint32_t checksum;              // 'h3C
}partition_hdr_t;



#endif

