#ifndef LWDS_HTML_PREPROCESSOR_H_
#define LWDS_HTML_PERPROCESSOR_H_

#include <string>
#include <unordered_map>

std::string Preprocess(std::string html,
                       std::unordered_map<std::string, std::string>& variables);

#endif  // LWDS_HTML_PERPROCESSOR_H_