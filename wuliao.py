#!/usr/bin/env python

import argparse
import os

CURRENT_DIR = os.path.dirname(os.path.realpath(__file__))


def read_config():
    parser = argparse.ArgumentParser(
        description='Why I lfeft language1 to language2')
    parser.add_argument(
        '-0',
        '--lan0', type=str, default='C',
        help='First disappointed with what language'
    )
    parser.add_argument(
        '-1',
        '--lan1', type=str, default='Java',
        help='Left language0 you found a new language '
        'but gona leave this language'
    )
    parser.add_argument(
        '-2',
        '--lan2', type=str, default='Python',
        help='You found the very language you love'
    )
    parser.add_argument(
        '-3',
        '--lan3', type=str, default='Python3',
        help='If that language also disappointed you We have another choise...'
    )
    parser.add_argument(
        '-t',
        '--temp', type=str, default=CURRENT_DIR + '/templates/en/article.md',
        help='Article contents'
    )
    parser.add_argument(
        '-p',
        '--lan1projects', type=str, nargs='+', default=['Spring MVC',
                                                        'Tomcat'],
        help='List the projects you was working on with language1'
    )
    parser.add_argument(
        '-o',
        '--output', type=str, default='',
        help='Save this article to you file'
    )
    return parser


def read_template(template_path):
    with open(template_path) as f:
        return f.read()


def save_template(file_path, content):
    with open(file_path, 'w+r') as f:
        f.write(content)


def read_helloworld(language):
    language = language.lower()
    prefix = language[0]
    hello_world_path = CURRENT_DIR + '/hello-world/' + prefix + '/'
    hello_world_full_path = ''
    for f in os.listdir(hello_world_path):
        t = f.lower()
        try:
            lan, ext = t.split('.')
            if lan == language:
                hello_world_full_path = hello_world_path + f
                break
        except:
            pass
    if hello_world_full_path:
        return read_template(hello_world_full_path)


def template_format(template, **kwargs):
    return template.format(
        **kwargs
    )


def run():
    parser = read_config()
    args = parser.parse_args()
    template = read_template(args.temp)
    hello1 = read_helloworld(args.lan1)
    hello2 = read_helloworld(args.lan2)
    fmt = template_format(
        template=template,
        language0=args.lan0,
        language1=args.lan1,
        language2=args.lan2,
        language1_hello_world=hello1,
        language2_hello_world=hello2,
        language3=args.lan3,
        project_names=', '.join(args.lan1projects)
    )
    if args.output:
        save_template(args.output, fmt)
    return fmt

if __name__ == '__main__':
    fmt = run()
    print fmt
