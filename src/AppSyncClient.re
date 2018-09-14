[@bs.module "aws-appsync"] [@bs.new]
external makeAWSAppSyncClient:
  {
    .
    "url": Js.Nullable.t(string),
    "region": Js.Nullable.t(string),
    "auth":
      Js.Nullable.t({
        .
        "type": string,
        "jwtToken": string,
      }),
  } =>
  'a =
  "AWSAppSyncClient";

let createAWSAppSyncClient = (~url=?, ~region=?, ~auth=?, ()) => {
  let appSyncClientOptions = {
    "url": Js.Nullable.fromOption(url),
    "region": Js.Nullable.fromOption(region),
    "auth": Js.Nullable.fromOption(auth),
  };
  makeAWSAppSyncClient(appSyncClientOptions);
};

type ampC;
[@bs.module "../../../src/aws-exports"]
external amplifyConfig: ampC = "default";
type amp;
[@bs.module "aws-amplify"] external amplify: amp = "default";

type c;
[@bs.send] external configure: (amp, ampC) => c = "configure";

let a = amplify;
let f = configure(a, amplifyConfig);

let config = AppSyncConfig.appSyncConfig;
let client = token =>
  createAWSAppSyncClient(
    ~url=config.graphqlEndpoint,
    ~region=config.region,
    ~auth={"type": config.authenticationType, "jwtToken": token},
    (),
  );
