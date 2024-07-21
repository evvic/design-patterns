# Singleton

> Not commonly used anymore
- A component which is instantiated once

## Motivation
- For some components it only makes sense to have one in the system
    - .i.e. one database, object factory
- When the constructor call is expensive and shouldn't be done again
- Want to prevent anyone from creating additional copies
- Want thread safety for the object