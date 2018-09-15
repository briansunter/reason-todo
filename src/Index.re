[%bs.raw {|require('../../../src/Index.scss')|}];

module AddButton = {
  let component = ReasonReact.statelessComponent("Todo");
  let make = _children => {
    ...component,
    render: _ =>
      <Router.NavLink route=Page2>
        <MaterialUi.Button className="fab" color=`Primary variant=`Fab />
      </Router.NavLink>,
  };
};

ReactDOMRe.renderToElementWithId(
  <Authenticator.WithAuthenticator>
    ...{
         (~authState) => {
           Js.log(authState);
           switch (authState) {
           | Some(s) =>
             <Router.WithRouter>
               ...(
                    (~currentRoute) =>
                      <ReasonApollo.Provider
                        client={
                          AppSyncClient.client(Authenticator.getToken(s))
                        }>
                        <App currentRoute />
                        <AddButton />
                      </ReasonApollo.Provider>
                  )
             </Router.WithRouter>

           | _ => <div />
           };
         }
       }
  </Authenticator.WithAuthenticator>,
  "root",
);
