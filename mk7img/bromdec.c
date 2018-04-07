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
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "bootrom.h"

// __STDC_VERSION__
#define C11_VERSION 201112
#define C99_VERSION 199901

int bootrom_decode(const char* img_name, uint8_t* buf, int len)
{
    bootrom_hdr_t* hdr;
    partition_hdr_t* parts;
    uint32_t offs;
    uint32_t attribute;
    int i;
    int j;

    if (len <= SZ_BOOTROM_HEADER) {
        printf("Error: %s too small\n", img_name);
        return -1;
    }

    printf("  total %d bytes\n", len);

    ////////////////////////////////////////////////////////
    hdr = (bootrom_hdr_t*)buf;

    for (i = 0;i < 8;i++) {
        printf("  interrupt[%d] : 0x%08X\n", i, hdr->interrupt_table[i]);
    }
    printf("  magic        : 0x%08X\n", hdr->qspi_width);
    printf("  id           : \"%.4s\"\n", (char*)&hdr->identification);
    if (hdr->encryption_status == EFUSE_KEY_ENCRYPTED) {
        printf("  encryption   : efuse key encrypted\n");
    } else if (hdr->encryption_status == RAM_KEY_ENCRYPTED) {
        printf("  encryption   : sram key encrypted\n");
    } else {
        printf("  encryption   : non-encrypted\n");
    }
    printf("  source_version        : 0x%08X\n", hdr->source_version);
    printf("  source_address        : 0x%08X\n", hdr->source_address);
    printf("  bytes_length          : 0x%08X\n", hdr->bytes_length);

    printf("  load_address          : 0x%08X\n", hdr->load_address);
    printf("  start_address         : 0x%08X\n", hdr->start_address);
    printf("  total_image_length    : 0x%08X\n", hdr->total_image_length);
    printf("  qspi_config           : 0x%08X\n", hdr->qspi_config);
    printf("  header_checksum       : 0x%08X\n", hdr->header_checksum);
    printf("  image_hdr_offset      : 0x%08X\n", hdr->image_hdr_offset);
    printf("  partition_hdr_offset  : 0x%08X\n", hdr->image_phdr_offset);
    printf("\n");

    printf("  registers_init@%04X:\n", (char*)hdr->registers_init - (char*)hdr);
    for (i = 0;i < 256;i++) {
        if (hdr->registers_init[2*i] == 0xFFFFFFFFu) {
            break;
        }
        printf("    0x%08X <= 0x%08X\n",
                hdr->registers_init[2*i],
                hdr->registers_init[2*i+1]);
    }
    if (i == 0) {
        printf("    (empty)\n");
    }
    printf("\n");

    offs = (char*)hdr->image_header - (char*)hdr;
    printf("  image_header@%04X - %04X\n",
            offs, offs + TOTAL_HEADER_SIZE + RSA_SIGNATURE_SIZE - 1);
    printf("\n");


    ////////////////////////////////////////////////////////
    offs = hdr->image_phdr_offset;
    if (offs + TOTAL_PARTITION_HEADER_SIZE > len) {
        printf("Error: %s too small\n", img_name);
        return -1;
    }

    parts = (partition_hdr_t*)((char*)hdr + offs);
    printf("  partition_headers@%04X\n", (char*)parts - (char*)hdr);

    for (i = 0;i < MAX_PARTITION_NUMBER;i++) {
        for (j = 0;j < IMAGE_HEADER_SIZE/sizeof(uint32_t)-1;j++) {
            if (((uint32_t*)&parts[i])[j] != 0) {
                break;
            }
        }
        if (j == IMAGE_HEADER_SIZE/sizeof(uint32_t)-1) {
            if (parts[i].checksum != 0xFFFFFFFF) {
                printf("Warning: invalid partition headers end entry...\n");
            }
            break;
        }

        printf("    image_length        0x%08X\n", parts[i].image_word_length * sizeof(uint32_t));
        printf("    data_length         0x%08X\n", parts[i].data_word_length * sizeof(uint32_t));
        printf("    partition_length    0x%08X\n", parts[i].partition_word_length * sizeof(uint32_t));
        printf("    load_address        0x%08X\n", parts[i].load_address);
        printf("    start_address       0x%08X\n", parts[i].start_address);
        printf("    partition_start     0x%08X\n", parts[i].partition_start);
        printf("    partition_attribute 0x%08X", parts[i].partition_attribute);
        attribute = parts[i].partition_attribute & ATTRIBUTE_IMAGE_TYPE_MASK;
        if (attribute == ATTRIBUTE_PS_IMAGE_MASK) {
            printf(" (PS-image)");
        }
        if (attribute == ATTRIBUTE_PL_IMAGE_MASK) {
            printf(" (PL-image)");
        }
        printf("\n");

        printf("    section_count       0x%08X\n", parts[i].section_count);
        printf("    md5sum_offset       0x%08X\n", parts[i].md5sum_offset);
        printf("    ac_offset           0x%08X\n", parts[i].ac_offset);
        printf("    checksum            0x%08X\n", parts[i].checksum);
        printf("\n");
    }


    return 0;
}

int main(int argc, char* argv[])
{
    FILE* fp;
    uint8_t* buf;
    int len;
    int retcode = 0;

    if (sizeof(bootrom_hdr_t) != SZ_BOOTROM_HEADER) {
        printf("Internal Error: expect sizeof(struct bootrom_hdr_t) %d, actual %d\n",
                SZ_BOOTROM_HEADER, sizeof(bootrom_hdr_t));
        return -1;
    }

    if (argc != 2) {
        printf("usage: %s boot.bin\n", argv[0]);
        return -1;
    }

    if ((fp = fopen(argv[1], "rb")) == NULL) {
        perror("Can't open file");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (len == 0) {
        printf("Error: zero length file \"%s\"\n", argv[1]);
        fclose(fp);
        return -1;
    }

    buf = (uint8_t*)malloc(len + 1);
    memset(buf, 0, len + 1);
    fread(buf, sizeof(uint8_t), len, fp);
    fclose(fp);

    retcode = bootrom_decode(argv[1], buf, len);

    free(buf);
    buf = NULL;

    return retcode;
}

