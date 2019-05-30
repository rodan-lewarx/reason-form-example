[@react.component]
let make = (~label, ~onChange, ~value, ~getErrorText) => {
  let errorText = getErrorText();
  BsReactstrap.(
    <FormGroup>
      <Label>
        {ReasonReact.string(label)}
        <Input
          value
          onChange
          invalid={Js.String.length(errorText) > 0 ? true : false}
        />
        {ReasonReact.string(errorText)}
      </Label>
    </FormGroup>
  );
};
