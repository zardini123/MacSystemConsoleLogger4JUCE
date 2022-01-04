# MacSystemConsoleLogger4JUCE

A small &amp; simple JUCE-module that redefines the JUCE [DBG macro](https://docs.juce.com/master/group__juce__core-system.html#ga679635952a5d2eb25f3b31398f0fcc25) to also output to the built in macOS application _Console.app_.

This repository is a forked from [JanosGit](https://github.com/JanosGit/MacSystemConsoleLogger4JUCE). JanosGit's original MacSystemConsoleLogger4JUCE method was to create a class that inherits from juce::Logger and redirects Log messages to NSLog. JanosGit's method required managing a object instance, and was recommended set [Logger::setCurrentLogger](https://docs.juce.com/master/classLogger.html#a5855a0341fc4f6ceb5418879fd685277) to the MacSystemConsoleLogger4JUCE logger. This method presented here does not require the user to do any object allocation, and instead use the `DBG()` macro as normally intended to debug.
