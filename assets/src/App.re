type state =
  | Idle
  | Loading
  | Error(string)
  | Result(Api.response);

type action =
  | Loaded(Api.response)
  | Failed(string)
  | Request
  | Reset;

let reducer = (state, action) =>
  switch (state, action) {
  | (Idle, Request) => Loading
  | (_, Reset) => Idle
  | (_, Loaded(r)) => Result(r)
  | (_, Failed(msg)) => Error(msg)
  | _ => state
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, Idle);

  React.useEffect1(
    () => {
      if (state == Loading) {
        let handle = response =>
          switch (response) {
          | Some(r) => dispatch(Loaded(r))
          | None => dispatch(Failed("api failure"))
          };

        handle |> Api.hello |> ignore;
      };
      None;
    },
    [|state|],
  );

  <div>
    <button disabled={state != Idle} onClick={_ => dispatch(Request)}>
      {React.string(state == Loading ? "loading" : "hello")}
    </button>
    <button onClick={_ => dispatch(Reset)} disabled={state == Idle}>
      {React.string("reset")}
    </button>
    {switch (state) {
     | Idle => React.null
     | Loading => <p> {React.string("Loading...")} </p>
     | Result(data) => <p> {React.string(data.hello)} </p>
     | Error(err) => <p> {React.string("Error: " ++ err)} </p>
     }}
  </div>;
};