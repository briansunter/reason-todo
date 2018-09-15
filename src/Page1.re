type todo = {name: string};
type todos = array(todo);
type items = option(todos);

type listTodos = {items};

module GetTodos = [%graphql
  {|
    query todos {
        listTodos(limit:100) @bsRecord{
          items @bsRecord {
            name
          }
        }
      }
|}
];

module AddButton = {
  let component = ReasonReact.statelessComponent("AddButton");
  let make = _children => {
    ...component,
    render: _ =>
      <Router.NavLink route=Page2>
        <MaterialUi.Button className="fab" color=`Primary variant=`Fab />
      </Router.NavLink>,
  };
};

module TodoItem = {
  let component = ReasonReact.statelessComponent("Todo");
  let make = (~todo: todo, _children) => {
    ...component,
    render: _ =>
      <li className="todoItem"> {ReasonReact.string(todo.name)} </li>,
  };
};

module TodoList = {
  let component = ReasonReact.statelessComponent("Todos");
  let make = (~todos: todos, _children) => {
    ...component,
    render: _ =>
      <div>
        <ul className="todoList">
          {
            ReasonReact.array(
              Array.mapi(
                (i, t) => <TodoItem key={string_of_int(i)} todo=t />,
                todos,
              ),
            )
          }
        </ul>
        <AddButton />
      </div>,
  };
};

let component = ReasonReact.statelessComponent("Page1");

module GetTodosQuery = ReasonApollo.CreateQuery(GetTodos);
let make = _children => {
  ...component,
  render: _ => {
    let todosQuery = GetTodos.make();
    <GetTodosQuery variables=todosQuery##variables>
      ...{
           ({result}) =>
             switch (result) {
             | Loading => <div> {ReasonReact.string("Loading")} </div>
             | Error(error) =>
               <div> {ReasonReact.string(error##message)} </div>
             | Data(response) =>
               switch (response##listTodos) {
               | Some({items: Some(items)}) => <TodoList todos=items />
               | _ => <div> {ReasonReact.string("No Todos")} </div>
               }
             }
         }
    </GetTodosQuery>;
  },
};
