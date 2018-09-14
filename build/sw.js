importScripts("precache-manifest.4f0bfda247d7df6f9755eadc77436e93.js", "https://storage.googleapis.com/workbox-cdn/releases/3.4.1/workbox-sw.js");

workbox.precaching.precacheAndRoute(self.__precacheManifest || []);
workbox.routing.registerNavigationRoute("/index.html");

