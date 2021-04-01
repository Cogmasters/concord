#ifndef ORKA_CONFIG_H
#define ORKA_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


struct orka_config {
  char *tag;

  char *fcontents; // config file contents
  size_t flen; // config file len

  FILE *f_http_dump; //default stderr
  void (*http_dump_cb)(
      _Bool show_code,  // if false code is ignored
      int code, 
      char *code_reason,
      struct orka_config* config, 
      char *url, 
      char *body);
};

void orka_config_init(struct orka_config*, const char tag[], const char config_file[]);
void orka_config_cleanup(struct orka_config*);

struct sized_buffer orka_config_get_field(struct orka_config *config, char *json_field);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ORKA_CONFIG_H
