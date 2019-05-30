[@react.component]
let make = () => {
  let (userState, setUserState) = React.useState(() => UserStates.Empty);

  React.useEffect0(() => {
    let decodeResults =
      Json.Decode.(
        field(
          "users",
          list((json) =>
            (
              {
                id: json |> field("id", string),
                email: json |> field("email", string),
                firstName: json |> field("firstName", string),
                lastName: json |> field("lastName", string),
              }: UserStates.userResponse
            )
          ),
        )
      );

    Js.Promise.(
      make((~resolve, ~reject) => resolve(. setUserState(_ => Loading)))
      |> then_(_ =>
           Fetch.fetchWithInit(
             "http://localhost:8000/api/users",
             Fetch.RequestInit.make(
               ~method_=Fetch.Get,
               ~headers=
                 Fetch.HeadersInit.make({"Content-Type": "application/json"}),
               (),
             ),
           )
         )
      |> then_(Fetch.Response.json)
      |> then_(json => decodeResults(json) |> resolve)
      |> then_(response => {
           switch (List.length(response)) {
           | 0 => setUserState(_ => UserStates.Empty)
           | _ => setUserState(_ => UserStates.Users(response))
           };
           resolve(None);
         })
      |> catch(_ => {
           setUserState(_ => UserStates.Error);
           resolve(None);
         })
    )
    |> ignore;
    None;
  });

  <React.Fragment>
    <PageHeading text="List Users" />
    <UserList userState />
  </React.Fragment>;
};
