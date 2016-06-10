FROM python
RUN pip install pip --upgrade
ADD ./ ./
WORKDIR ./
RUN pip install -r ./requirements.txt
EXPOSE 80
CMD ["gunicorn", "app:app", "-b", "0.0.0.0:80", "-w", "4"]
