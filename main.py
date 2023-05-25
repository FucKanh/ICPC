import streamlit as st
import code_search
import code_upload

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