type response = {hello: string};

module Decode = {
  let hello = json => Json.Decode.{hello: json |> field("msg", string)};
};

let hello = callback =>
  Js.Promise.(
    Fetch.fetch("/api/hello")
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json
         |> Decode.hello
         |> (
           response => {
             callback(Some(response));
             resolve();
           }
         )
       )
    |> catch(_err => {
         callback(None);
         resolve();
       })
  );