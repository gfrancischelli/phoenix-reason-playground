defmodule HelloWeb.HelloController do
  use HelloWeb, :controller

  def index(conn, _params) do
    json(conn, %{msg: "Hello World!"})
  end
end
