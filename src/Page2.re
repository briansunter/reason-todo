module AddTodo = [%graphql
  {|
   mutation createTodo($name: String!) {
     createTodo(input: {name: $name}){
       name id
       }
     }
|}
];

module AddTodoMutation = ReasonApollo.CreateMutation(AddTodo);

type state = {todoName: string};
type actions =
  | UpdateTodoName(string)
  | SaveTodo;

let component = ReasonReact.reducerComponent("Page2");

let make = _children => {
  ...component,
  initialState: () => {todoName: ""},
  reducer: (a, s) =>
    switch (a) {
    | UpdateTodoName(n) => ReasonReact.Update({todoName: n})
    | SaveTodo => ReasonReact.UpdateWithSideEffects(s, (ss => Js.log(ss)))
    },
  render: _self =>
    <div className="Page2">
      <AddTodoMutation>
        ...{
             (mutation, _) =>
               <div>
                 <h1> {ReasonReact.string("Add Todo")} </h1>
                 <MaterialUi.TextField
                   value={`String(_self.state.todoName)}
                   onChange={
                     event =>
                       _self.send(
                         UpdateTodoName(
                           ReactEvent.Form.target(event)##value,
                         ),
                       )
                   }
                 />
                 <MaterialUi.Button
                   onClick={
                     _ => {
                       let newTodo =
                         AddTodo.make(~name=_self.state.todoName, ());
                       Js.log(newTodo);
                       mutation(
                         ~variables=newTodo##variables,
                         ~refetchQueries=[|"listTodos"|],
                       )
                       |> (r => Js.log(r()));
                     }
                   }>
                   <p> {ReasonReact.string("save")} </p>
                 </MaterialUi.Button>
               </div>
           }
      </AddTodoMutation>
    </div>,
};
