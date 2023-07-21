import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore

def send_data_to_firebase():
    # Firebaseのサービスアカウント情報
    cred = credentials.Certificate('./test-cpp-to-firebase-firebase-adminsdk-ruihs-55eb777c49.json')
    app = firebase_admin.initialize_app(cred)
    db = firestore.client()

    doc_ref = db.collection("positions").document("test")
    doc_ref.set({"x": 100, "y": 200, "z": 50})
    print("added")

send_data_to_firebase()