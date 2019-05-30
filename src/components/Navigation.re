[@react.component]
let make = () => {
  <React.Fragment>
    BsReactstrap.(
      <Navbar color="light" light=true expand="md">
        <NavbarBrand>
          {ReasonReact.string("Reason Form Example ")}
        </NavbarBrand>
        <Nav vertical=false>
          <NavItem>
            <Button
              color="link" onClick={() => ReasonReactRouter.push("/addUser")}>
              {ReasonReact.string("Add User")}
            </Button>
          </NavItem>
          <NavItem>
            <Button
              color="link"
              onClick={() => ReasonReactRouter.push("/listUsers")}>
              {ReasonReact.string("List Users")}
            </Button>
          </NavItem>
        </Nav>
      </Navbar>
    )
  </React.Fragment>;
};
