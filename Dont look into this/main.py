import streamlit as st
from streamlit_authenticator import Authenticate, Hasher
from upload_and_search import uploadNsearch

@st.cache_data
def init_class():
    return uploadNsearch()

def main():

    upload_and_search = init_class()
    code_search,code_upload = st.tabs(['Search code','Submit code'])

    with code_search:
        upload_and_search.codeSearch()

    with code_upload:
        upload_and_search.uploadCode()
        

if __name__ == '__main__':
    main()