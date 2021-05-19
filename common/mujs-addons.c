ORCAcode orcajs_run(
  js_State *J, 
  struct user_agent *ua, 
  struct sized_buffer *resp_body,
  int *p_nparam)
{
  int nparam = js_gettop(J);
  *p_nparam = nparam;
  jsB_log("number of parameters: %d\n", nparam);

  enum http_method method;
  if (!js_isstring(J, 1)) {
    jsB_log(TAG ".do_url expect a METHOD string\n");
    //js_error(J, "HttpGet.do expect a url parameter");
    exit(1);
  }

  char *strmethod = (char *)js_tostring(J, 1);
  jsB_log("method: %s\n", strmethod);
  method = http_method_eval(strmethod);

  if (!js_isstring(J, 2)) {
    jsB_log(TAG ".do_url expect a url string\n");
    //js_error(J, "HttpGet.do expect a url parameter");
    exit(1);
  }

  char *url = (char *)js_tostring(J, 2);
  jsB_log("url:%s\n", url);

  char *buf=NULL;
  struct ua_resp_handle  resp_handle = \
    { .ok_cb = copy_resp, .ok_obj = &buf };

  struct sized_buffer req_body={}
  if (4 == nparam) { // has body
    if (js_isobject(J, 3) || js_isstring(J, 3)) {
      req_body.start = (char *)js_tostring(J, 3);
      req_body.size = strlen(req_body.start);
      jsB_log("request body: %.*s\n", (int)req_body.size, req_body.start);
    }
  }

  struct ua_info *info; // can be used to extract info on the transfer
  ORCAcode code = ua_vrun(
                    ua, 
                    &info, 
                    &resp_handle, 
                    &req_body, 
                    method, url, args);

  *resp_body = (struct sized_buffer){
    .start = buf,
    .size = buf ? strlen(buf) : 0
  };

  return code;
}
