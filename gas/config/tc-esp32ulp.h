/* tc-esp32ulp.h

ESP32ULP GNU Assembler

Copyright (c) 2016-2017 Espressif Systems (Shanghai) PTE LTD.

based on Copyright (C) 2005-2017 Free Software Foundation, Inc.

This file is part of GAS, the GNU Assembler.

GAS is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GAS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GAS; see the file COPYING.  If not, write to the Free
Software Foundation, 51 Franklin Street - Fifth Floor, Boston, MA
02110-1301, USA.  */

#define TC_ESP32ULP 1

#define TARGET_BYTES_BIG_ENDIAN 0
//#define OCTETS_PER_BYTE_POWER 2

#define TARGET_ARCH		bfd_arch_esp32ulp

/*
* Define the target format macro here.   The value for this should be
* "elf32-esp32ulp", not "elf32-little-esp32ulp".  Since the BFD source file
* elf32-esp32ulp.c defines TARGET_LITTLE_NAME to be "elf32-little-esp32ulp",
* we must use this value, until this is corrected and BFD is rebuilt.  */
#ifdef OBJ_ELF
#define TARGET_FORMAT		"elf32-esp32ulp"
#endif

#define LISTING_HEADER "ESP32ULP GAS "

#define WORKING_DOT_WORD

extern bfd_boolean esp32ulp_start_label(char *);

#define md_number_to_chars	number_to_chars_littleendian
#define md_convert_frag(b,s,f)	as_fatal ("esp32ulp convert_frag\n");

/* Allow for [, ], etc.  */
#define LEX_BR 6

#define TC_EOL_IN_INSN(PTR) (esp32ulp_eol_in_insn(PTR) ? 1 : 0)
extern bfd_boolean esp32ulp_eol_in_insn(char *);

#define TC_EQUAL_IN_INSN(C, NAME) 1

#define NOP_OPCODE 0x0000

#define LOCAL_LABELS_FB 1

#define DOUBLESLASH_LINE_COMMENTS

#define TC_START_LABEL(STR, NUL_CHAR, NEXT_CHAR)	\
  (NEXT_CHAR == ':' && esp32ulp_start_label (STR))
#define tc_fix_adjustable(FIX) esp32ulp_fix_adjustable (FIX)
extern bfd_boolean esp32ulp_fix_adjustable(struct fix *);

#define TC_FORCE_RELOCATION(FIX) esp32ulp_force_relocation (FIX)
extern int esp32ulp_force_relocation(struct fix *);

/* Call md_pcrel_from_section(), not md_pcrel_from().  */
#define MD_PCREL_FROM_SECTION(FIX, SEC) md_pcrel_from_section (FIX, SEC)
extern long md_pcrel_from_section(struct fix *, segT);

/* Values passed to md_apply_fix3 don't include symbol values.  */
#define MD_APPLY_SYM_VALUE(FIX) 0

/* This target is buggy, and sets fix size too large.  */
#define TC_FX_SIZE_SLACK(FIX) 2

extern unsigned int esp32ulp_anomaly_checks;

/* Anomaly checking */
#define AC_05000074 0x00000001
#define ENABLE_AC_05000074 (esp32ulp_anomaly_checks & AC_05000074)

/* Branch conditions for jump instructions */

#define BRCOND_EQ 3 
#define BRCOND_GT 4
#define BRCOND_LE 2
#define BRCOND_LT 0
#define BRCOND_GE 1


/* end of tc-esp32ulp.h */
