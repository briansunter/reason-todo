[%bs.raw {|require('../../../node_modules/@aws-amplify/ui/dist/style.css')|}];
[@bs.module "aws-amplify-react"]
external authenticator: ReasonReact.reactClass = "Authenticator";

type authData = string;

let getToken: authData => string = [%raw
  {|
  function(a){
    return a.signInUserSession.idToken.jwtToken;
  }
  |}
];

[@bs.module "aws-amplify-react"]
module Authenticator = {
  type authState = string;
  type onStateChange = (authState, authData) => unit;

  let make = (~onStateChange, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=authenticator,
      ~props={"onStateChange": onStateChange},
      children,
    );
};

module WithAuthenticator = {
  type state = {authData: option(authData)};

  type action =
    | Update(authData);

  let component = ReasonReact.reducerComponent("WithAuthenticator");
  let make = children => {
    ...component,
    initialState: () => {authData: None},
    reducer: (a: action, s) =>
      switch (a) {
      | Update(d) => ReasonReact.Update({authData: Some(d)})
      },
    render: self =>
      <Authenticator onStateChange={(s, d) => self.send(Update(d))}>
        {children(~authState=self.state.authData)}
      </Authenticator>,
  };
};
