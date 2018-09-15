[%bs.raw {|require('../../../src/Index.scss')|}];

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
