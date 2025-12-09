struct LockCommand {
  const char* command;
  
  public:
    static LockCommand fromJson(JsonDocument& doc) {
      LockCommand cmd;
      cmd.command = doc["command"];
      return cmd;
    }
};