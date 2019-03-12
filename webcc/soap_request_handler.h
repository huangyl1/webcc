#ifndef WEBCC_SOAP_REQUEST_HANDLER_H_
#define WEBCC_SOAP_REQUEST_HANDLER_H_

#include <map>
#include <string>

#include "webcc/http_request_handler.h"
#include "webcc/soap_globals.h"

namespace webcc {

class SoapRequestHandler : public HttpRequestHandler {
public:
  explicit SoapRequestHandler(SoapVersion soap_version)
      : soap_version_(soap_version), format_raw_(true) {
  }

  ~SoapRequestHandler() override = default;

  void set_format_raw(bool format_raw) {
    format_raw_ = format_raw;
  }

  void set_indent_str(const std::string& indent_str) {
    indent_str_ = indent_str;
  }

  bool Bind(SoapServicePtr service, const std::string& url);

private:
  void HandleConnection(HttpConnectionPtr connection) final;

  SoapServicePtr GetServiceByUrl(const std::string& url);

  typedef std::map<std::string, SoapServicePtr> UrlServiceMap;
  UrlServiceMap url_service_map_;

  // Default to kSoapV12.
  SoapVersion soap_version_;

  // Format response XML without any indentation or line breaks.
  bool format_raw_;

  // Indent string for response XML.
  // Applicable when |format_raw_| is false.
  std::string indent_str_;
};

}  // namespace webcc

#endif  // WEBCC_SOAP_REQUEST_HANDLER_H_
