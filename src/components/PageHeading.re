[@react.component]
let make = (~text) =>
  <React.Fragment>
    <h4
      style={ReactDOMRe.Style.make(
        ~paddingTop="1em",
        ~paddingBottom="1em",
        (),
      )}>
      {ReasonReact.string(text)}
    </h4>
  </React.Fragment>;
