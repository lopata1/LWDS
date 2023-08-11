#include <lwds/pages/page.h>

Page::Page(PageData page_data) { page_data_ = page_data; }

HttpResponse Page::Handle() {
  if (page_data_.request.method_ == HttpMethod::GET) return HandleGet();
  return HandlePost();
}

HttpResponse Page::HandlePost() { return HandleGet(); }