typedef enum {
    NULL_TAG = 0,
    FB_ALLOCATE_BUFFER = 0x00040001,
    FB_RELESE_BUFFER = 0x00048001,
    FB_GET_PHYSICAL_DIMENSIONS = 0x00040003,
    FB_SET_PHYSICAL_DIMENSIONS = 0x00048003,
    FB_GET_VIRTUAL_DIMENSIONS = 0x00040004,
    FB_SET_VIRTUAL_DIMENSIONS = 0x00048004,
    FB_GET_BITS_PER_PIXEL = 0x00040005,
    FB_SET_BITS_PER_PIXEL = 0x00048005,
    FB_GET_BYTES_PER_ROW = 0x00040008
} property_tag_t;

typedef struct {
  void * fb_addr;
  long fb_size;
} fb_allocate_res_t;

typedef struct {
  long width;
  long height;
} fb_screen_size_t;

/*
 * The value buffer can be any one of these types
 */
typedef union {
  long fb_allocate_align;
  fb_allocate_res_t fb_allocate_res;
  fb_screen_size_t fb_screen_size;
  long fb_bits_per_pixel;
  long fb_bytes_per_row;
} value_buffer_t;

/*
 * A message_buffer can contain any number of these
 */
typedef struct {
  property_tag_t proptag;
  value_buffer_t value_buffer;
} property_message_tag_t;
