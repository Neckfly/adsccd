all: registration_proto_python

registration_proto_python: olympic_games_registration.proto
	protoc --python_out=. olympic_games_registration.proto

clean:
	rm olympic_games_registration_pb2.py