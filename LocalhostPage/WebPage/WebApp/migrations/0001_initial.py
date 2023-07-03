# Generated by Django 4.1.3 on 2023-06-27 10:27

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Dht',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('date', models.DateTimeField(blank=True, null=True)),
                ('temp', models.FloatField(blank=True, null=True)),
                ('hum', models.FloatField(blank=True, null=True)),
            ],
            options={
                'db_table': 'dht',
                'managed': False,
            },
        ),
        migrations.CreateModel(
            name='Doortrigger',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('date', models.DateTimeField(blank=True, null=True)),
            ],
            options={
                'db_table': 'doortrigger',
                'managed': False,
            },
        ),
    ]
