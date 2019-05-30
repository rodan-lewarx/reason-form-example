[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch (url.path) {
  | ["listUsers"] => <ListUsers />
  | ["addUser"] => <AddUser />
  | [] => <ListUsers />
  | _ => <div> {ReasonReact.string("Sorry, page not found")} </div>
  };
};
