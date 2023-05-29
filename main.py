import streamlit as st
import authenticator
import upload_and_search

def main():
    code_search,code_upload = st.tabs([
        'Tìm code',
        'Thêm code'
    ])

    with code_search:
        pass

    with code_upload:
        pass
    

if __name__ == '__main__':
    main()