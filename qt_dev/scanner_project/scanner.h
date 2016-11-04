#ifndef SCANNER_H
#define SCANNER_H

#include "logger.h"
#include <stdint.h>
#include <assert.h>
#include <sane/sane.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

typedef struct
{
  uint8_t *data;
  int width;
  int height;
  int x;
  int y;
}Image;

#define STRIP_HEIGHT	256
static SANE_Handle device = NULL;
static int verbose;
static int progress = 0;
static SANE_Byte *buffer;
static size_t buffer_size;

SANE_Status get_device(const SANE_Device *** device_list,SANE_Bool local_only);
SANE_Status start_scan(SANE_Handle sane_handle, SANE_String_Const fileName);
SANE_Status do_scan(const char *fileName);
static void write_pnm_header (SANE_Frame format, int width, int height, int depth, FILE *ofp);
static SANE_Status scan_it (FILE *ofp);
static SANE_Status scan_it (FILE *ofp);

int scanner(char *loc)
{
    SANE_Device scanner;
    SANE_Option_Descriptor options;
    SANE_Int version_code;
    SANE_Status start;
    SANE_Bool local_only=SANE_TRUE;
    const SANE_Device **device_list=NULL,*runner;
    SANE_Handle handler;
    //device_list = (SANE_Device *)malloc(sizeof(SANE_Device));
    //SANE_String_Const c = *device_list.name;
    //device_list.name = "aap";
    //printf("name = %s\n",*device_list(name));
//	device_list = malloc(sizeof(SANE_Device));
//	device_listImage = NULL;
    start = sane_init (&version_code,NULL);
    if (start>0) {
        printf("Initialisation failed with error: %s\n",sane_strstatus(start));
    } else {
            start = get_device(&device_list,local_only);
        if (start<0) {
        }
        else
        {
            if (device_list == NULL) {
                printf("No devices connected\n");
            } else {
                runner = *device_list;
                printf("printer name: %s\n",runner->name);
                /*for (runner; runner!=NULL;runner++)
                {
                    printf("printer name: %s\n",runner->name);
                }*/
                start = sane_open(runner->name, &handler);

                if(start>0)
                {
                    printf("Failed to open device, %s with error: '%s'",runner->name, sane_strstatus(start));
                } else {
                    start = start_scan(handler,loc);
                    sane_close(handler);
                }
            }

        }
    }

//	free(device_list);
    printf("sane status = %d ",start);
    sane_exit();
    return 0;
}

SANE_Status get_device(const SANE_Device *** device_list,SANE_Bool local_only)
{
    SANE_Status start = (SANE_Status) 0;
    start = sane_get_devices(device_list, local_only);
    if (start >0)
    {
        printf("Error getting Device List: %s\n",sane_strstatus(start));
        return start;
    }
    return start;

}
SANE_Status start_scan(SANE_Handle sane_handle, SANE_String_Const fileName)
{
    SANE_Status sane_status = (SANE_Status)0;
    device = sane_handle;
    // if (sane_status = sane_start(sane_handle))
    // {
    //     printf("sane_start status: %s\n", sane_strstatus(sane_status));
    // }
    // return sane_status;
    return do_scan(fileName);
}

SANE_Status do_scan(const char *fileName)
{
    SANE_Status status;
    FILE *ofp = NULL;
    char path[PATH_MAX];
    char part_path[PATH_MAX];
    buffer_size = (32 * 1024);
        buffer = (SANE_Byte *) malloc (buffer_size);

    do
    {
        int dwProcessID = getpid();
        sprintf (path, "%s%d.pnm", fileName, dwProcessID);
        strcpy (part_path, path);
        strcat (part_path, ".part");

        status = sane_start (device);
        if (status != SANE_STATUS_GOOD)
        {
            break;
        }

        if (NULL == (ofp = fopen (part_path, "w")))
        {
            status = SANE_STATUS_ACCESS_DENIED;
            break;
        }

        status = scan_it (ofp);

        switch (status)
        {
            case SANE_STATUS_GOOD:
            case SANE_STATUS_EOF:
                 {
                      status = SANE_STATUS_GOOD;
                      if (!ofp || 0 != fclose(ofp))
                      {
                          status = SANE_STATUS_ACCESS_DENIED;
                          break;
                      }
                      else
                      {
                          ofp = NULL;
                          if (rename (part_path, path))
                          {
                              status = SANE_STATUS_ACCESS_DENIED;
                              break;
                          }
                      }
                  }
                  break;
            default:
                  break;
        }
    }while (0);

    if (SANE_STATUS_GOOD != status)
    {
        sane_cancel (device);
    }
    if (ofp)
    {
        fclose (ofp);
        ofp = NULL;
    }
    if (buffer)
    {
        free (buffer);
        buffer = NULL;
    }

    return status;
}

static SANE_Status scan_it (FILE *ofp)
{
    int i, len, first_frame = 1, offset = 0, must_buffer = 0, hundred_percent;
    SANE_Byte min = 0xff, max = 0;
    SANE_Parameters parm;
    SANE_Status status;
    Image image = { 0, 0, 0, 0, 0 };
    static const char *format_name[] = {"gray", "RGB", "red", "green", "blue"};
    SANE_Word total_bytes = 0, expected_bytes;
    SANE_Int hang_over = -1;

    do
    {
        if (!first_frame)
        {
            status = sane_start (device);
            if (status != SANE_STATUS_GOOD)
            {
                goto cleanup;
            }
        }

        status = sane_get_parameters (device, &parm);
        if (status != SANE_STATUS_GOOD)
        {
          goto cleanup;
        }

        if (first_frame)
        {
            switch (parm.format)
            {
                case SANE_FRAME_RED:
                case SANE_FRAME_GREEN:
                case SANE_FRAME_BLUE:
                  //assert (parm.depth == 8);
                  must_buffer = 1;
                  offset = parm.format - SANE_FRAME_RED;
                  break;
                case SANE_FRAME_RGB:
                  assert ((parm.depth == 8) || (parm.depth == 16));
                case SANE_FRAME_GRAY:
                    assert ((parm.depth == 1) || (parm.depth == 8) || (parm.depth == 16));
                    if (parm.lines < 0)
                    {
                        must_buffer = 1;
                        offset = 0;
                    }
                    else
                    {
                        write_pnm_header (parm.format, parm.pixels_per_line,parm.lines, parm.depth, ofp);
                    }
                  break;
                default:
                  break;
            }

            if (must_buffer)
            {
                image.width = parm.bytes_per_line;
                if (parm.lines >= 0)
                    image.height = parm.lines - STRIP_HEIGHT + 1;
                else
                    image.height = 0;

                image.x = image.width - 1;
                image.y = -1;
                /*if (!advance (&image))
                {
                    status = SANE_STATUS_NO_MEM;
                    goto cleanup;
                }*/
            }
        }
        else
        {
            assert (parm.format >= SANE_FRAME_RED && parm.format <= SANE_FRAME_BLUE);
            offset = parm.format - SANE_FRAME_RED;
            image.x = image.y = 0;
        }

        hundred_percent = parm.bytes_per_line * parm.lines * ((parm.format == SANE_FRAME_RGB || parm.format == SANE_FRAME_GRAY) ? 1:3);

        while (1)
        {
            double progr;
            status = sane_read (device, buffer, buffer_size, &len);
            total_bytes += (SANE_Word) len;
            progr = ((total_bytes * 100.) / (double) hundred_percent);
            if (progr > 100.)
                progr = 100.;

            if (status != SANE_STATUS_GOOD)
            {
                if (status != SANE_STATUS_EOF)
                {
                    return status;
                }
                break;
            }

            if (must_buffer)
            {
                switch (parm.format)
                {
                    case SANE_FRAME_RED:
                    case SANE_FRAME_GREEN:
                    case SANE_FRAME_BLUE:
                        for (i = 0; i < len; ++i)
                        {
                            image.data[offset + 3 * i] = buffer[i];
                            /*if (!advance (&image))
                            {
                                status = SANE_STATUS_NO_MEM;
                                goto cleanup;
                            }*/
                        }
                        offset += 3 * len;
                        break;
                    case SANE_FRAME_RGB:
                        for (i = 0; i < len; ++i)
                        {
                            image.data[offset + i] = buffer[i];
                           /* if (!advance (&image))
                            {
                                status = SANE_STATUS_NO_MEM;
                                goto cleanup;
                            }*/
                        }
                        offset += len;
                        break;
                    case SANE_FRAME_GRAY:
                        for (i = 0; i < len; ++i)
                        {
                            image.data[offset + i] = buffer[i];
                           /* if (!advance (&image))
                            {
                                status = SANE_STATUS_NO_MEM;
                                goto cleanup;
                            }*/
                        }
                        offset += len;
                        break;
                    default:
                        break;
                }
            }
            else			/* ! must_buffer */
            {
                if ((parm.depth != 16))
                    fwrite (buffer, 1, len, ofp);
                else
                {
#if !defined(WORDS_BIGENDIAN)
                    int i, start = 0;
                    /* check if we have saved one byte from the last sane_read */
                    if (hang_over > -1)
                    {
                        if (len > 0)
                        {
                            fwrite (buffer, 1, 1, ofp);
                            buffer[0] = (SANE_Byte) hang_over;
                            hang_over = -1;
                            start = 1;
                        }
                    }
                    /* now do the byte-swapping */
                    for (i = start; i < (len - 1); i += 2)
                    {
                        unsigned char LSB;
                        LSB = buffer[i];
                        buffer[i] = buffer[i + 1];
                        buffer[i + 1] = LSB;
                    }
                    /* check if we have an odd number of bytes */
                    if (((len - start) % 2) != 0)
                    {
                        hang_over = buffer[len - 1];
                        len--;
                    }
#endif
                    fwrite (buffer, 1, len, ofp);
                }
            }

            if (verbose && parm.depth == 8)
            {
              for (i = 0; i < len; ++i)
                if (buffer[i] >= max)
                    max = buffer[i];
                else if (buffer[i] < min)
                    min = buffer[i];
            }
        }
        first_frame = 0;
    }while (!parm.last_frame);

    if (must_buffer)
    {
        image.height = image.y;
        write_pnm_header (parm.format, parm.pixels_per_line,image.height, parm.depth, ofp);

#if !defined(WORDS_BIGENDIAN)
        if (parm.depth == 16)
        {
            int i;
            for (i = 0; i < image.height * image.width; i += 2)
            {
                unsigned char LSB;
                LSB = image.data[i];
                image.data[i] = image.data[i + 1];
                image.data[i + 1] = LSB;
            }
        }
#endif
        fwrite (image.data, 1, image.height * image.width, ofp);
    }

    fflush( ofp );

cleanup:
    if (image.data)
        free (image.data);

    return status;
}

static void write_pnm_header (SANE_Frame format, int width, int height, int depth, FILE *ofp)
{
    switch (format)
    {
        case SANE_FRAME_RED:
        case SANE_FRAME_GREEN:
        case SANE_FRAME_BLUE:
        case SANE_FRAME_RGB:
            fprintf (ofp, "P6\n# SANE data follows\n%d %d\n%d\n", width, height, (depth <= 8) ? 255 : 65535);
            break;
        default:
            if (depth == 1)
                fprintf (ofp, "P4\n# SANE data follows\n%d %d\n", width, height);
            else
                fprintf (ofp, "P5\n# SANE data follows\n%d %d\n%d\n", width, height,(depth <= 8) ? 255 : 65535);
            break;
    }
}

#endif // SCANNER_H
