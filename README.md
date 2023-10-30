<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/ctapiero/Lab6">
    <img src="logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">LAB 6</h3>

  <p align="center">
    This project evaluates the production/consumption ratio to prevent overflow. Classifies timing requirements as hard, firm, or soft real-time requirements Prioritize tasks based on timing     requirements.
    <br />
    <a href="https://github.com/ctapiero/Lab6"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/ctapiero/Lab6">View Demo</a>
    ·
    <a href="https://github.com/ctapiero/Lab6/issues">Report Bug</a>
    ·
    <a href="https://github.com/ctapiero/Lab6/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This project was part 6 of several Labs for ECE 6960 Advanced Embedded Systems
<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![cpp][cpp-shield]][cpp-url]


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

Clone this Repo

### Prerequisites

Using platformio run the following command
* pio
  ```sh
  pio project init --board disco_f072rb --project-option "framework=zephyr"
  ```


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES 
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_

<p align="right">(<a href="#readme-top">back to top</a>)</p> -->



<!-- ROADMAP -->
## Roadmap

- [x] Activity 0 We fixed the bug in the code and figured out how the code works. the output is printing from main and from the other thread.
- [x] Activity 1 We refactored the code in activity 0 to protect the critical sections (the counter and printing).
- [x] Activity 2 we wrote the functions test_semaphore_unlocked() and test_semaphore_locked().
- [x] Activity 3 Ashton removed it.
- [x] Activity 4 created the lock and test it with  test_semaphore_deadlock().
- [ ] Activity 5

See the [open issues](https://github.com/ctapiero/lab6/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Your Name - [@twitter_handle](https://twitter.com/twitter_handle) - email@email_client.com

Project Link: [https://github.com/ctapiero/Lab6](https://github.com/ctapiero/Lab6)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* []()
* []()
* []()

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/ctapiero/Lab6.svg?style=for-the-badge
[contributors-url]: https://github.com/ctapiero/Lab6/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/ctapiero/Lab6.svg?style=for-the-badge
[forks-url]: https://github.com/ctapiero/Lab6/network/members
[stars-shield]: https://img.shields.io/github/stars/ctapiero/Lab6.svg?style=for-the-badge
[stars-url]: https://github.com/ctapiero/Lab6/stargazers
[issues-shield]: https://img.shields.io/github/issues/ctapiero/Lab6.svg?style=for-the-badge
[issues-url]: https://github.com/ctapiero/Lab6/issues
[license-shield]: https://img.shields.io/github/license/ctapiero/Lab6.svg?style=for-the-badge
[license-url]: https://github.com/ctapiero/Lab6/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/linkedin_username
[product-screenshot]: images/screenshot.png
[cpp-shield]: https://img.shields.io/badge/-c++-black?logo=c%2B%2B&style=social
[cpp-url]: https://cplusplus.com/
[React.js]: https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB
[React-url]: https://reactjs.org/
[Vue.js]: https://img.shields.io/badge/Vue.js-35495E?style=for-the-badge&logo=vuedotjs&logoColor=4FC08D
[Vue-url]: https://vuejs.org/
[Angular.io]: https://img.shields.io/badge/Angular-DD0031?style=for-the-badge&logo=angular&logoColor=white
[Angular-url]: https://angular.io/
[Svelte.dev]: https://img.shields.io/badge/Svelte-4A4A55?style=for-the-badge&logo=svelte&logoColor=FF3E00
[Svelte-url]: https://svelte.dev/
[Laravel.com]: https://img.shields.io/badge/Laravel-FF2D20?style=for-the-badge&logo=laravel&logoColor=white
[Laravel-url]: https://laravel.com
[Bootstrap.com]: https://img.shields.io/badge/Bootstrap-563D7C?style=for-the-badge&logo=bootstrap&logoColor=white
[Bootstrap-url]: https://getbootstrap.com
[JQuery.com]: https://img.shields.io/badge/jQuery-0769AD?style=for-the-badge&logo=jquery&logoColor=white
[JQuery-url]: https://jquery.com 

