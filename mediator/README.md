# Mediator
- Fascilitates communication between components
    - Without them necessarily being aware of each other
    - Or having direct (reference) acces to each other

## Motivation
- Components may go in and out of the system at anytime
    - i.e. chat room or online game
- It makes no sense for the components to have direct reference to one another
    - These references could be deleted
- Therefore having them refer to a central componenet ("mediator") that fascilitates communication

