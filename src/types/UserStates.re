type userResponse = {
  id: string,
  email: string,
  firstName: string,
  lastName: string,
};

type userStateType =
  | Error
  | Empty
  | Loading
  | Users(list(userResponse));
