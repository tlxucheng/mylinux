#ifdef __cplusplus
extern "C" {
#endif

    int    xp_replace(const char *source, char *dest, const char *search, const char *replace);
    int    xp_set_xml_buffer_from_string(const char * str);
    int    xp_set_xml_buffer_from_file(const char * filename);
    char * xp_open_element(int index);
    void   xp_close_element();
    int    xp_search_element_from_name(const char * element, int occurence);
    char * xp_get_value(const char * name);
    char * xp_get_cdata();
    int    xp_get_content_length(const char * P_buffer);

#ifdef __cplusplus
}
#endif

