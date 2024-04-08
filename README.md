# How to use these programs

The fastest way to use these projects is by using CodeBlocks 17.12 with build-in Allegro library which is in this repository in the folder ,,CodeBlocks". All you need to do is change path Compiler's installation directory in Global compiler settings (Settings tab -> Compiler) to subfolder MinGW.

If there was error with Allegro library, you need to in Project tab -> Build Options-> Other Linker Options, add 
-lallegro-5.0.10-monolith-mt.

## Advection equation
The advection equation describes the process of transferring a physical quantity (e.g. mass, energy or substance concentration) through a moving medium. The main relation it takes into account is the flow velocity, which is responsible for the movement of this amount through space. The advection equation is often described by a one-dimensional partial differential equation, although it can also be extended to the multidimensional case.

$$\frac{\partial u}{\partial t}+v\frac{\partial u}{\partial x}=0$$

The solved equation by Lax method:

$$u_i^{n+1}=\frac{1}{2}(u_{i+1}^n+u_{i-1}^n)-\frac{v\Delta t}{2h}(u_{i+1}^n+u_{i-1}^n)$$

and the midpoint method:

$$u_i^{n+1}=u_i^{n-1}-\frac{v\Delta t}{2h}(u_{i+1}^n+u_{i-1}^n)$$

The aim of the project was to investigate the solution for selected initial and boundary conditions and plot the dependence of u(x,t) for selected time instants and the change in half-width over time.

## Diffusion equation
The diffusion equation can be formulated in many ways, depending on the context and the type of diffusion we are dealing with. However, the basic diffusion equation is known as a second-order partial differential equation, which describes the diffusion process in one or more spaces dimensions. In the case of one-dimensional diffusion, the diffusion equation is of the form:

$$\frac{\partial u}{\partial t}=D \frac{\partial^2 u}{\partial x^2}$$

The diffusion equation has many important applications. It can be used to describe the diffusion of chemicals in porous media, the spread of heat in solids, the transport of molecules in biological tissues and many other processes in which diffusion occurs.

The algorithm is as follows:

$$u_j^{n+1}=u_j^n+\frac{D\Delta t}{h^2}(u_{j+1}^n-2u_j^n+u_{j-1}^n)$$

The aim of the project was to investigate the issue for selected initial and boundary points.

## EM field
In the presence of a constant magnetic field and a constant electric field, charged particles can experience forces and accelerations that significantly affect their trajectory and kinematics. There are two key interactions: the Lorentz force in a magnetic field and the electrostatic force in an electric field.

$$m\vec{r}"=e\vec{E}+\frac{e}{c}\vec{v}~\times~\vec{B}$$

$$E=E_x+iE_y$$

The Lorentz force is the result of the interaction between the magnetic field and the motion of a charged particle moving at a certain speed. This force is perpendicular to both the direction of motion of the particle and the direction of the magnetic field. Its value depends on the intensity of the magnetic field, the charge of the particle and the speed at which the particle is moving. An electric field, on the other hand, induces an electrostatic force on a charged particle. This force depends on the charge of the particle and the intensity of the electric field. If the particle has a positive charge, the electrostatic force acts in the direction opposite to the electric field, whereas if the particle has a negative charge, the force acts in the same direction as the electric field.

A solution variation follows:

$$v_{n+1}=\frac{e}{m}\Delta t(\frac{1-i\alpha}{1+\alpha^2})E+(\frac{1-\alpha^2-2i\alpha}{1+\alpha^2})v_n$$

The aim of the project was to investigate the problem for different initial conditions and to determine the kinetic, potential and total energies.

## Fibriogen
The Random Sequential Adsorption (RSA) method was first used to describe the adsorption of proteins on surfaces and was described in the article 'Colloid Interface Sci. 78, 144 (1980)'. The RSA model neglects interactions between molecules, meaning that the forces of attraction or repulsion between adsorbents are not considered. The shape of the molecules is approximated to the form of disks,
which is a simplification to facilitate mathematical analysis. The method makes it possible to determine the maximum random coverage of surfaces by adsorbate objects (for example, proteins) and the kinetics of their deposition. The RSA method makes it possible to determine what maximum surface coverage can be achieved under conditions of random adsorption of molecules. A limitation of the model is that it only predicts that at most a monolayer of molecules can be deposited, reflecting a situation where molecules adsorb onto a surface in a single layer.
The aim of the project was to write a programme showing the adsorption of fibrinogen molecules, made up of beads:

The small spheres have a diameter of 1.5nm, the middle one 5.3nm and the outer ones 6.7nm. Investigate the coverage of the substrate with fibrinogen molecules by fitting a Feder curve $\theta(\infty)-\theta(t)\sim t^{-1/d}$ to a plot of coverage against time, where $\theta(\infty)$ is the coverage of the maximum area, $\theta(t)$ is the coverage at time $t$ and $d$ is the number of degrees of freedom of the deposited objects. 

Coverage:

$$\theta(t)=absorbed~particles\frac{fibriogen~surface}{substrat~surface}$$

## Flat wave
A flat wave polarised in a vacuum is a specific type of electromagnetic wave in which the electric field oscillates in a single plane, called the plane of polarisation.

$$\left\{\begin{matrix}
\frac{\partial B}{\partial t}+c\frac{\partial E}{\partial x}=0\\ 
\frac{\partial E}{\partial t}+c\frac{\partial B}{\partial x}=0
\end{matrix}\right.$$

In the case of a plane wave polarised in a vacuum, the electric field vector and the magnetic field vector are mutually perpendicular and perpendicular to the direction of wave propagation. Depending on the orientation of the electric field vector in the plane of polarisation, we can distinguish between different types of polarisation, such as linear, elliptical or circular polarisation. We will solve by the method:

$$\left\{\begin{matrix}
E_j^{n+1}=\frac{1}{2}(E_{j+1}^n+E_{j-1}^n)-\frac{1}{2}(B_{j+1}^n-B_{j-1}^n)\frac{c\Delta t}{h}\\ 
B_j^{n+1}=\frac{1}{2}(B_{j+1}^n+B_{j-1}^n)-\frac{1}{2}(E_{j+1}^n-E_{j-1}^n)\frac{c\Delta t}{h}
\end{matrix}\right.$$

The aim of the project was to investigate the dependence of $E(x,t)$ and $B(x,t)$ for selected time instants for different systems of equations. The boundary conditions are periodic, we only change the initial conditions, that is, the system of equations $E$ and $B$.

## Fly
The fruit fly, or Drosophila melanogaster, is an object of intense research due to its complex biology and important contribution to genetic studies. However, in recent years, interest has also been directed to a more macroscopic level - understanding the collective behaviour of midges in the context of active matter. 

The position of the fly in polar coordinates:

$$\textbf{r}(t)=\begin{pmatrix}
r(t)cos(\beta(t))\\ 
r(t)sin(\beta(t))
\end{pmatrix}$$

Its change:

$$\frac{d\textbf{r}(t)}{dt}=\textbf{v}(t)=\begin{pmatrix}
v_0(t)cos(\theta(t))\\ 
v_0(t)sin(\theta(t))
\end{pmatrix}$$

Necessary notations:

$$z(t)=\theta(t)-\beta(t)$$

$$\beta(t)=arctan\frac{y(t)}{x(t)}$$

Given two variables $U_1$ and $U_2$ with a uniform distribution on the segment (0,1), perform a transformation to obtain variables with a Levy distribution with parameter $\alpha$:

$$V=\pi(U_1-\frac{1}{2})$$

$$W=-log(U_2)$$

$$X=\left\{\begin{matrix}
\frac{sin(\alpha V)}{cos(V)^(1/\alpha)}[\frac{cos((\alpha-1)V)}{W}]^{\frac{1-\alpha}{\alpha}},\alpha \neq 1\\ 
tan(V), \alpha = 1
\end{matrix}\right$$

Trajectory of the fly's eyes as follows:

$$\theta(t+\Delta t)=\theta(t)+\kappa sin(\theta - \beta)\Delta t +\frac{\sigma}{v_0}X\Delta t^{\frac{1}{\alpha}}$$

The aim of the project was to write a programme to visualise the movement of a fruit fly and to analyse the paths of movement as a function of the parameters $\alpha$ and $\sigma$.

## Fractal

The Limit Diffusion Aggregation (DLA) method is a model that has been introduced as a way to model aggregation processes in physics and other fields. The process consists of: placing a single particle at an initial point in the coordinate system. This molecule is usually considered the seed from which the aggregation process starts. Subsequent particles are added by random wandering. They start their movement from a random point in space. Each particle moves randomly, choosing its route at random. If a new molecule encounters a previously formed aggregate (also known as a cluster), it joins it. This phenomenon simulates the process of aggregation, where new molecules join existing ones. This process is repeated, adding more molecules that move randomly, joining the aggregate when they encounter it. This process results in structures that often exhibit fractal properties. These structures are highly complex and full of detail at different scales. It is used to simulate the formation of structures such as dendrites in crystallisation, plant growth patterns, or structures in chemical reactions. This technique is also used in computer graphics to generate fractals and nature-like structures.


The aim of the project was to write a programme to visualise the deposition of molecules in square geometry using the DLA method for a square lattice, with the initial molecule placed in the centre of the lattice. 
## Lennard-Jones potential

## Lotka-Volterra equation

The Lotka-Volterra equation - a non-linear system of first-degree differential equations. The following model was proposed in 1926 by Vito Volterra to describe fish populations caught in the Adriatic Sea. Independently of Volterra, equivalent equations to describe the oscillation of substance concentrations in a hypothetical chemical reaction were obtained by Alfred James Lotka in 1920. The Lotka-Volterra equation is a model for dynamic systems occurring in ecosystems, e.g. in simulating the behaviour of prey and predator populations.

$$\begin{matrix}
\frac{dx}{dt} = (a-by)x\\ 
\frac{dy}{dt} = (cx-d)y
\end{matrix}$$

a - prey birth rate or prey growth rate, 
c - birth rate of predators or growth rate of predators, 
d - predator death rate or predator attrition rate, 
b - prey death rate due to predation. 
The main drawback of the basic Lotka-Volterra model is that with a zero predator population prey abundance increases indefinitely.

## Isigna model
The Ising model is a mathematical physical model that was proposed by physicist Ernst Ising in 1925. The model is used in statistical physics to study the magnetic properties of substances and to analyse phase transitions in physical systems. The main purpose of the Ising model is to describe magnetism in solids by taking into account the interactions between the spins of atoms or magnetic dipole moments. The model is a simple but important tool for understanding the collective behaviour of spins in magnetic bodies. In the Ising model, each atom or molecule in a solid has a spin that can take on one of two values: 'up'or 'down', which corresponds to the direction of magnetism. The atoms are arranged on a regular lattice and neighbouring spins interact with each other, leading to magnetic properties.

$$H=-\frac{1}{2}\sum_{<i,j>}J_{ij}\sigma_i \sigma_j-\sum_i h_i \sigma_i$$

where: h - spin energy in the external megnetic field, $J_{ij}$ - exchange integral The Ising model is often used in the context of statistical physics to analyse phase behaviour, such as ferromagnetic transitions
or antiferromagnetic transitions.

$$J_{ij}>0~-~ferromagnetic$$
$$J_{ij}<0~-~antiferromagnetic$$
$$J_{ij}=0~-~no interaction$$

Magnetisation:

$$M=\frac{1}{N}\sum_i <\sigma_i>$$

Magnetic susceptibility:

$$\chi=\frac{1}{T}[<M^2>-<M>^2]$$

Specific heat:

$$C=\frac{1}{T^2}[<E^2>-<E>^2]$$

The aim of the project was to solve the Isigna model problem in 2D, determining the temperature dependence of the mean magnetisation and energy, and to draw the magnetic susceptibility and specific heat from temperature.

## XY model
The XY model, also known as the Heisenberg XY model, is one of the key models in statistical physics, particularly in the context of the theory of magnetism. The interactions between spins in magnetic systems are analysed within the framework of this model, which has found application mainly in the study of ferromagnets. The Hamiltonian is given by the equation:

$$H=-J\sum_{<i,j>}s_i*s_j=-J\sum_{<i,j>}\cos{\theta_i-\theta_j}$$

Where the sum runs over all pairs of nearest spins of S, while J is the coupling constant.
Model with external field:

$$H(s)=-\sum_{i\neq j}J_{ij} s_i * s_j - \sum_j h_j*s_j=-\sum_{i\neq j}J_{ij}\cos{\theta_i-\theta_j}-\sum_j h_j \cos{\theta_j}$$

The XY model is often used to analyse phase transitions, particularly the Curie transition, which represents the loss of global magnetisation as temperature increases. This model is characterised by continuous symmetry, meaning that changes in the spin angle value are continuous, which differs from models that describe spins as vectors with finite directions.

The aim of the project was to solve the XY model, determining the average magnetisation and energy from temperature, and the magnetic susceptibility and specific heat from temperature. 

## Needles
The aim of the project was to write a programme in which two random sections are visualised. Generate a random configuration of non-overlapping sections with a given density $\rho = N/(L∗L)$.

## Newton cannon
Newton's cannon is a thought experiment created by Isaac Newton to explain the orbital motion of the moon. Basically, why the moon does not fall to Earth if it feels the acceleration caused by gravity. Also why the moon, which moves with constant speed and constant direction and does not feel any external force, does not move in a straight line but in a circle. To clarify these issues, Newton carried out an experiment in which a cannon was placed on a high mountain top and a projectile was fired horizontally. After comparing two formulae for the distance a cannonball will travel horizontally and vertically, it can be seen that the horizontal distance ($d_x=\vec{v} \times t$) depends on its velocity. Newton then realised that if he chose the right velocity, the trajectory of the cannonball would curve to exactly the same extent as the curvature of the Earth, so the cannonball would always remain at the same height above the ground. By doing so, he balanced the inertia of the cannonball, which makes it want to continue its journey in a straight line, and therefore away from the Earth, with the acceleration caused by the Earth's gravity. As a result, the cannonball orbits the Earth, always accelerating towards it but never approaching it. Ultimately, Newton concluded that the speed of the cannonball is related to the acceleration due to the Earth's gravity ($\vec{a}$) and the radius of the orbit ($\vec{r}$ - measured from the centre of the orbit; i.e. the centre of the Earth) as follows:

The aim of the project was to solving Newton's cannon:
$$\frac{d^2\vec{r}(t)}{dt^2}=-\frac{GM}{r(t)^3}\vec{r}(t),$$

$$\vec{r}(t=0)=(0,R),$$

$$\vec{v}(t=0)=(V,0).$$
Representation of orbits after changes in the value of V , assuming G = M = R = 1. Determine the dependence of the error depending on the method of integration of the equation of motion (Euler, Euler-Cromer and Ruge-Kutta order 4) and the step dt, comparing with the analytical solution:
$$r(t)=\frac{R^2V^2}{GM+\sqrt{G^2M^2+R^2V^2(-\frac{2GM}{R}+V^2)}~cos(\varphi (t) - \varphi_0)}.$$

## Onsager model
Lars Onsager studied the special case in which molecules are elongated and interact with each other via an intermolecular potential V(1,2), which depends on the position and orientation of the molecules labelled ,,1" and ,,2". His work in this area was primarily concerned with the theory of liquid crystalline systems. For such a system, Onsager developed a formalism based on chemical and external potentials, which allowed him to describe the Helmholtz free energy F for such a system.

$$\beta F=\int \rho(1)[log(\rho(1)\Lambda^3)-1-\beta \mu+\beta U(1)]d(1)-\frac{1}{2}\int f(1,2)\rho(1)\rho(2)d(2)d(1)$$

where: $\beta=\frac{1}{kT}$,$\Lambda$ is the de Broglie thermal wavelength, $mu$ is the chemical potential, U is the external potential and f(1,2) is the Meyer function:

$$f(1,2)=e^{-\frac{V(1,2)}{kT}}-1$$

By introducing temperature-dependent expansion coefficients, Onsager was able to derive detailed equations describing the thermodynamic properties of crystalline liquids. The free energy per molecule is equal to:

$$\frac{\beta F}{N}=\frac{\beta F_0}{N}+\int f(\theta_1)[log(df(\theta_1)-1-\beta \mu)]d\theta_1+\frac{d}{2}\int V_{excl}(\theta_1,\theta_2)f(\theta_1)f(\theta_2)d\theta_1 d\theta_2$$

where $V_{excl}$ is the excluded volume of two needles oriented at angles $theta_1$ and $theta_2$ are the orientations of the molecules, $f(\theta)$ is the probability density of finding a molecule at angle q, $mu$ the chemical potential, and d is the density of molecules per unit area. We calculate the distribution profile of the angles of the molecules by minimising the free energy. Hence:

$$log[f(\theta_1)]=-d\int V_{excl}(\theta_1,\theta_2)f(\theta_2)d\theta_2-log(d)-\beta \mu$$

We can designate the order parameter as:

$$S=\int_0^{2\pi}\cos{2\theta}f(\theta)d\theta$$

The aim of the project was to plot the dependence of the order parameter on the density of the system $S=(0,0.1,0.2,0.3,...,10)$.
## Poisson-Laplace equation
The Laplace equation is a second-degree partial differential equation that occurs in the context of harmonic functions. It can be used to describe many physical phenomena, such as the distribution of temperature, electrical potential or the distribution of gravitational potential. In the two-dimensional case, Laplace's equation takes the form:
$$\Delta U = 0$$
Poisson's equation is an extension of Laplace's equation and takes into account the presence of sources in the field. It can be used in cases where there is a source or an outflow of some type of substance, such as electric charges, masses or heat. In the two-dimensional case, the Poisson equation takes the form:
$$\Delta U = -\frac{\rho}{\epsilon}$$
where $\rho$ is the source density and $\epsilon$ is the dielectric permeability.

The aim of the project was to investigate the problem for selected initial and boundary conditions, assuming several point sources.

## Pseudorandom number generator 

## Quantum billard

## Scattering

## Wave equation
Wave equations are a type of partial differential equations that describe the propagation of waves in space and time. They apply to different types of waves, such as sound waves, electromagnetic waves, seismic waves or mechanical waves. In general, these equations describe the changes in the value of a certain quantity (e.g. pressure, electric field, strain) as a function of time and position in space. Wave equations are usually in the form of second-order differential equations, which take into account the second time and spatial derivatives of the quantity under study.

$$\frac{\partial^2 u}{\partial t^2}=c^2\frac{\partial^2 u}{\partial x^2}$$.

By solving the wave equations, the shape, amplitude and propagation of the waves in a given system can be determined. There are many techniques and numerical methods for solving the wave equations, such as differential methods, finite elements, spectral methods or wave propagation methods. This allows complex wave phenomena to be simulated and analysed, predicting their behaviour under different conditions and environments. 

The aim of the project was to investigate the dependence of $u(x,t)$ for selected time instants and the change in the shape of the solution over time for selected initial and boundary conditions. This will be obtained by the method:

$$u_j^{n+1}=(\frac{c\Delta t}{h})^2(u_{j+1}^2-2u_j^n+u_{j-1}^n)+2u_j^n-u_j^{n-1}$$
