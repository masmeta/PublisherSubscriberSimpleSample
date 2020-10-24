# Publisher Subscriber Simple Sample
A simple example of the publisher subscriber pattern with C++


In ‘Publisher-Subscriber’ pattern, senders of messages, called publishers, do not program the messages to be sent directly to specific receivers, called subscribers.

This means that the publisher and subscriber don’t know about the existence of one another. There is a third component, called broker or message broker or event bus, which is known by both the publisher and subscriber, which filters all incoming messages and distributes them accordingly. In other words, pub-sub is a pattern used to communicate messages between different system components without these components knowing anything about each other’s identity. how does the broker filter all the messages? Actually, there are several processes for message filtering. Most popular methods are: Topic-based and Content-based. Well, not going to further on that road, if you are interested. Here is the schematic diagram  (Pub-Sub Pattern (image credit: MSDN blog)) :

[Pub-Sub Pattern](github.com/masmeta/PublisherSubscriberSimpleSample/assets/schematic diagram.gif)

## Getting started

The software uses the standard libraries. You have to use cmake and make to generate the executable.
In your root project :
```
mkdir build
cd build/
cmake ..
make
./subpubSample
```
## Links 

This site was built using [GitHub Pages](https://pages.github.com/).

More informations : 
* [Wikipedia](https://fr.wikipedia.org/wiki/Publish-subscribe)
* [Article By: Matthew O’Riordan](https://www.ably.io/topic/pub-sub)

## Versions

* **Latest stable release :** 1.0
* **Latest release:** 1.0

## Authors

* **Guillaume Sauvage** _alias_ [@masmeta](https://https://github.com/masmeta)

## Licence

This project is under license ``WTFTPL`` - view file [LICENSE.md](LICENSE.md) for more informations.
