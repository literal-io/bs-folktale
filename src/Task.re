type t('value, 'error);

module Executor = {
  type t('value);
  [@bs.send] external cancel : t('value) => unit = "";
  [@bs.send] external promise : t('value) => Js.Promise.t('value) = "";
};

module Resolver = {
  type t('value, 'error);
  [@bs.send.pipe : t('value, 'error)]
  external onCleanup : (unit => unit) => unit = "cleanup";
  [@bs.send.pipe : t('value, 'error)]
  external onCancelled : (unit => unit) => unit = "";
  [@bs.send.pipe : t('value, 'error)] external resolve : 'value => unit = "";
  [@bs.send.pipe : t('value, 'error)] external reject : 'error => unit = "";
  [@bs.send] external cancel : t('value, 'error) => unit = "";
  [@bs.get] external isCancelled : t('value, 'error) => bool = "";
};

[@bs.val] [@bs.module "folktale/concurrency/task"]
external rejected : 'error => t('value, 'error) = "";

[@bs.val] [@bs.module "folktale/concurrency/task"]
external of_ : 'value => t('value, 'error) = "of";

[@bs.val] [@bs.module "folktale/concurrency/task"]
external make : (Resolver.t('value, 'error) => unit) => t('value, 'error) =
  "task";

[@bs.send] external run : t('value, 'error) => Executor.t('value) = "";

[@bs.send.pipe : t('value, 'error)]
external chain : ('value => t('newValue, 'newError)) => t('newValue, 'newError) =
  "";

[@bs.send.pipe : t('value, 'error)]
external and_ : t('value, 'error) => t(array('value), 'error) = "and";
