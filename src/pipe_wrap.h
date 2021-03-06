// Copyright Joyent, Inc. and other Node contributors.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef SRC_PIPE_WRAP_H_
#define SRC_PIPE_WRAP_H_

#if defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#include "async-wrap.h"
#include "connection_wrap.h"
#include "env.h"

namespace node {

class PipeWrap : public ConnectionWrap<PipeWrap, uv_pipe_t> {
 public:
  static v8::Local<v8::Object> Instantiate(Environment* env, AsyncWrap* parent);
  static void Initialize(v8::Local<v8::Object> target,
                         v8::Local<v8::Value> unused,
                         v8::Local<v8::Context> context);

  size_t self_size() const override { return sizeof(*this); }

 private:
  PipeWrap(Environment* env,
           v8::Local<v8::Object> object,
           bool ipc,
           AsyncWrap* parent);

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Bind(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Listen(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Connect(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Open(const v8::FunctionCallbackInfo<v8::Value>& args);

#ifdef _WIN32
  static void SetPendingInstances(
      const v8::FunctionCallbackInfo<v8::Value>& args);
#endif
};


}  // namespace node

#endif  // defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#endif  // SRC_PIPE_WRAP_H_
