module StateLenses = [%lenses
  type state = {
    email: string,
    firstName: string,
    lastName: string,
  }
];
module AddUserForm = ReFormNext.Make(StateLenses);

type responseStatus =
  | NotSent
  | Error
  | Success(string);

[@react.component]
let make = () => {
  let (result, setResult) = React.useState(() => NotSent);

  let {state, submit, getFieldState, handleChange}: AddUserForm.api =
    AddUserForm.use(
      ~schema={
        AddUserForm.Validation.Schema([|
          Email(Email),
          Custom(
            FirstName,
            values =>
              Js.String.length(values.firstName) > 4
              || Js.String.length(values.firstName) === 0
                ? Valid
                : Error(
                    "First Name must be empty or have more than 4 characters",
                  ),
          ),
          Custom(
            LastName,
            values =>
              Js.String.length(values.lastName) > 4
                ? Valid : Error("Last Name must have more than 4 characters"),
          ),
        |]);
      },
      ~onSubmit=
        ({state}) => {
          let body =
            Json.Encode.(
              object_([
                ("email", string(state.values.email)),
                ("firstName", string(state.values.firstName)),
                ("lastName", string(state.values.lastName)),
              ])
            )
            |> Json.stringify;

          Fetch.fetchWithInit(
            "http://localhost:8000/api/user",
            Fetch.RequestInit.make(
              ~method_=Fetch.Post,
              ~body=Fetch.BodyInit.make(body),
              ~headers=
                Fetch.HeadersInit.make({"Content-Type": "application/json"}),
              (),
            ),
          )
          |> Js.Promise.(
               then_(response => {
                 let decodeResults =
                   Json.Decode.(field("createdUserId", Json.Decode.string));

                 switch (response |> Fetch.Response.status) {
                 | 200 =>
                   response
                   |> Fetch.Response.json
                   |> then_(json => resolve(decodeResults(json)))
                   |> then_(createdUserId => {
                        setResult(_ => Success(createdUserId));
                        resolve(createdUserId);
                      })
                   |> ignore
                 | _ => setResult(_ => Error)
                 };
                 resolve();
               })
             )
          |> ignore;
          None;
        },
      ~initialState={email: "", firstName: "", lastName: ""},
      (),
    );

  let resetFields = () => {
    handleChange(Email, "");
    handleChange(FirstName, "");
    handleChange(LastName, "");
  };

  React.useEffect1(
    () => {
      switch (result) {
      | Success(_) => resetFields()
      | _ => ()
      };
      None;
    },
    [|result|],
  );

  let onFieldChange = fieldName =>
    ReForm.Helpers.handleDomFormChange(handleChange(fieldName));

  let getErrorText = (fieldName, ()) => {
    getFieldState(Field(fieldName))
    |> (
      fun
      | Error(error) => Some(error)
      | _ => None
    )
    |> Belt.Option.getWithDefault(_, "");
  };

  BsReactstrap.(
    <Form
      onSubmit={event => {
        ReactEvent.Synthetic.preventDefault(event);
        submit();
      }}>
      <InputField
        label="Email:"
        value={state.values.email}
        onChange={onFieldChange(Email)}
        getErrorText={getErrorText(Email)}
      />
      <InputField
        label="First Name:"
        value={state.values.firstName}
        onChange={onFieldChange(FirstName)}
        getErrorText={getErrorText(FirstName)}
      />
      <InputField
        label="Last Name:"
        value={state.values.lastName}
        onChange={onFieldChange(LastName)}
        getErrorText={getErrorText(LastName)}
      />
      <div>
        <Button color="primary"> {ReasonReact.string("Submit")} </Button>
        <Button color="secondary" onClick={_ => resetFields()}>
          {ReasonReact.string("Clear Form")}
        </Button>
      </div>
    </Form>
  );
};
