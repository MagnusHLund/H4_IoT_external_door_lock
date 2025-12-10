struct LockCommand {
  const char* command;
  const char* token;
  
  public:
    static LockCommand fromJson(JsonDocument& doc) {
      LockCommand cmd;
      cmd.command = doc["command"];
      cmd.token = doc["token"];
      return cmd;
    }
};