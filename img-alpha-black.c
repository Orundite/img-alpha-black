#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
#include <fcntl.h>
#include <io.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>

#if defined(_WIN32) || defined(_WIN64)
#define cfprintf fwprintf
#define cprintf wprintf
#define cc(x) L##x
#else
#define cfprintf fprintf
#define cprintf printf
#define cc(x) x
#endif


void write_to_file_callback(void *context, void *data, int size) {
  fwrite(data, 1, size, (FILE *)context);
}

#if defined(_WIN32) || defined(_WIN64)
int wmain(int argc, wchar_t **argv)
#else
int main(int argc, char **argv)
#endif
{

#if defined(_WIN32) || defined(_WIN64)
  _setmode(_fileno(stderr), _O_U16TEXT);
#endif
  if (argc != 3) {
    cfprintf(stderr, cc("Usage: app [source_image] [destination_image]\n"));
    return 1;
  }
  int width, height, channels;

#if defined(_WIN32) || defined(_WIN64)
  FILE *file = NULL;
  errno_t err = _wfopen_s(&file, argv[1], L"rb");
#else
  FILE *file = fopen(argv[1], "rb");
#endif
  if (!file) {
    cfprintf(stderr, cc("Error: Cannot open source file\n"));
    return 1;
  }
  stbi_uc *img = stbi_load_from_file(file, &width, &height, &channels, 2);

  fclose(file);
  file = NULL;

  if (img == NULL) {
    cfprintf(stderr, cc("Error: Failed to load image\n"));
    return 1;
  }
  int total_pixels = width * height;
  for (int i = 0; i < total_pixels; i++) {
    int index = i * 2;
    stbi_uc temp = img[index];
    img[index + 1] = img[index];
    img[index] = 0;
  }

#if defined(_WIN32) || defined(_WIN64)
  err = _wfopen_s(&file, argv[2], L"wb");
#else
  file = fopen(argv[2], "wb");
#endif

  if (file) {
    int stride_in_bytes = width * 2;
    int result=stbi_write_png_to_func(write_to_file_callback, file, width, height, 2, img,
                           stride_in_bytes);
    fclose(file);
    if(result==0)
    {
      stbi_image_free(img);
      cfprintf(stderr, cc("Error: Failed to save image\n"));
      return 1;
    }

  } else {
    stbi_image_free(img);
    cfprintf(stderr, cc("Error: Cannot create destination file. Perhaps the directory does not exist (use mrkdir)\n"));
    return 1;
  }
  
  stbi_image_free(img);
  return 0;
}
