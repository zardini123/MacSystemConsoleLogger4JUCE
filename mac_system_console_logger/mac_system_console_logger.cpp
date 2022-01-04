/*
MIT License

Copyright (c) 2018 Janos Buttgereit

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "mac_system_console_logger.h"

#if (defined(JUCE_DEBUG) && !defined(JUCE_DISABLE_ASSERTIONS)) && (defined(JUCE_MAC) || defined(JUCE_IOS))

// macOS specific code must be done in a .mm file, which in turn will be
//    compiled by macOS specific stuff.
// Including (importing) Foundation/Foundation.h outside a .mm file results in
//    some insane compile errors regarding multiple defintions, where types from
//    Foundation and JUCE intersect.
// Therefore the workaround is to use a function header in the DBG macro,
//    and the function body becomes defined once this .mm file is compiled.
// The DBG macro is re-defined in the header file as the macro needs to be
//    included immediately before it is used in code.
//    The macro definition cannot be deffered as for some reason defining a
//    macro in a .mm file does not transfer to the user code.
// Note, JUCE in juce_BasicNativeHeaders.h also does #import instead of #include
#import <Foundation/Foundation.h>

namespace mac_system_console_logger {
  void mac_system_console_logger(const juce::String &message) {
      juce::String tempDbgBuf;
      tempDbgBuf << message;
      juce::Logger::outputDebugString(tempDbgBuf);

      CFStringRef messageCFString = tempDbgBuf.toCFString();
      // Put plugin name in log message to seperate DAW messages from plugin messages
      // JucePlugin_Name is defined as a macro via JUCE-created compile arguments
      CFStringRef pluginNameCFString = CFStringCreateWithCString(NULL, JucePlugin_Name, kCFStringEncodingUTF8);

      NSLog(@"%@: %@", (NSString *)pluginNameCFString, (NSString *)messageCFString);

      CFRelease(messageCFString);
      CFRelease(pluginNameCFString);
  }
}

#endif
