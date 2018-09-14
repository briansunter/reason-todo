type a;
[@bs.module "aws-amplify"] external auth: a = "Auth";

type s;
[@bs.send] external currentSession: a => s = "currentUserCredentials";
let fee = currentSession(auth);

type t = {
  graphqlEndpoint: string,
  region: string,
  authenticationType: string,
  jwtToken: s,
};

let appSyncConfig = {
  graphqlEndpoint: "https://5klatcsifjenflbvf6rm7g44nu.appsync-api.us-east-1.amazonaws.com/graphql",
  region: "eu-east-1",
  authenticationType: "AMAZON_COGNITO_USER_POOLS",
  jwtToken: fee,
};
