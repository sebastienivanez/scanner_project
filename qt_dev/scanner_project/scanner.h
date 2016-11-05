#ifndef SCANNER_H
#define SCANNER_H

#include "logger.h"
#include <stdint.h>
#include <assert.h>
#include <sane/sane.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

typedef struct {
  uint8_t *data;
  int width;
  int height;
  int x;
  int y;
} Image;

SANE_Status get_device(const SANE_Device *** device_list,SANE_Bool local_only);
SANE_Status start_scan(SANE_Handle sane_handle, SANE_String_Const fileName);
SANE_Status do_scan(const char *fileName);
static void write_pnm_header (SANE_Frame format, int width, int height, int depth, FILE *ofp);
static SANE_Status scan_it (FILE *ofp);
static SANE_Status scan_it (FILE *ofp);
int scanner(char *loc);
SANE_Status get_device(const SANE_Device *** device_list,SANE_Bool local_only);
SANE_Status start_scan(SANE_Handle sane_handle, SANE_String_Const fileName);
SANE_Status do_scan(const char *fileName);

#endif // SCANNER_H
