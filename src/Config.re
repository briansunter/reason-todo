type routes =
  | Home
  | Page1
  | Page2
  | Page3;

let routeToString =
  fun
  | Home => "/"
  | Page1 => "/page1"
  | Page2 => "/page2"
  | Page3 => "/page3";

let urlToRoute: ReasonReact.Router.url => routes =
  url =>
    switch (url.path) {
    | ["page1"] => Page1
    | ["page2"] => Page2
    | ["page3"] => Page3
    | _ => Home
    };

let routeToTitle = route =>
  switch (route) {
  | Home => "Home"
  | Page1 => "Page1"
  | Page2 => "Page2"
  | Page3 => "Page3"
  };
