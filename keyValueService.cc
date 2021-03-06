
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "keyValue.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using keyValue::KeyValueStore;
using keyValue::PutRequest;
using keyValue::PutReply;
using keyValue::GetRequest;
using keyValue::GetReply;
using keyValue::DeleteRequest;
using keyValue::DeleteReply;

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
    
    Status Get(ServerContext* context, const GetRequest* request,
               GetReply* reply) override {
        std::string key(request->key);
        return Status::OK;
    }
    
    Status Put(ServerContext* context, const PutRequest* request,
                         PutReply* reply) override {
        std::string key(request->key);
        std::string value(request->value);
        return Status::OK;
    }
    
    Status Delete(ServerContext* context, const DeleteRequest* request,
               DeleteReply* reply) override {
        std::string key(request->key);
        
        return Status::OK;
    }
};

void RunServer() {
  std::string server_address("0.0.0.0:50000");
  GreeterServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
