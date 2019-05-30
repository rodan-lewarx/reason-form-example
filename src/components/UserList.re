let s = ReasonReact.string;

[@react.component]
let make = (~userState) => {
  <React.Fragment>
    BsReactstrap.(
      <Table>
        <thead>
          <tr>
            <th> {s("#")} </th>
            <th> {s("Email")} </th>
            <th> {s("First Name")} </th>
            <th> {s("Last Name")} </th>
          </tr>
        </thead>
        <tbody>
          {switch (userState) {
           | UserStates.Empty =>
             <tr> <td colSpan=4> {s("Database ho no users yet.")} </td> </tr>
           | UserStates.Error =>
             <tr> <td colSpan=4> {s("Error while loading data.")} </td> </tr>
           | UserStates.Loading =>
             <tr> <td colSpan=4> {s("Loading Data...")} </td> </tr>
           | UserStates.Users(response) =>
             response
             |> List.mapi((i, user: UserStates.userResponse) =>
                  <tr key={user.id}>
                    <td> {s(string_of_int(i + 1))} </td>
                    <td> {s(user.email)} </td>
                    <td> {s(user.firstName)} </td>
                    <td> {s(user.lastName)} </td>
                  </tr>
                )
             |> Array.of_list
             |> ReasonReact.array
           }}
        </tbody>
      </Table>
    )
  </React.Fragment>;
};
