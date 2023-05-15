program MatrixProduct
    implicit none

    integer :: i, j, dimensao
    integer, allocatable :: A(:,:), x(:), b(:), resultado(:)
    real :: tempo_inicio, tempo_fim, tempo_total, tempo_inicio_rev, tempo_fim_rev, tempo_total_rev

    dimensao = 80000

    allocate(A(dimensao, dimensao))
    allocate(x(dimensao))
    allocate(b(dimensao))
    allocate(resultado(dimensao))

    call srand(0)

    do i = 1, dimensao
        do j = 1, dimensao
            A(i,j) = mod(int(rand()*10), 10)
        end do
        x(i) = mod(int(rand()*10), 10)
    end do

    call cpu_time(tempo_inicio_rev)
    call matvecrev(A, x, resultado, dimensao, dimensao)
    call cpu_time(tempo_fim_rev)

    tempo_total_rev = tempo_fim_rev - tempo_inicio_rev
    write(*,*) "Tempo para a dimensao com loop aninhado invertido", dimensao, ": ", tempo_total_rev, " segundos"

    call cpu_time(tempo_inicio)
    call matvec(A, x, resultado, dimensao, dimensao)
    call cpu_time(tempo_fim)

    tempo_total = tempo_fim - tempo_inicio
    write(*,*) "Tempo para a dimensao com loop aninhado normal", dimensao, ": ", tempo_total, " segundos"


    deallocate(A)
    deallocate(x)
    deallocate(b)
    deallocate(resultado)

contains

    subroutine matvec(A, x, b, nrows, ncols)
        integer, intent(in) :: nrows, ncols
        integer, intent(in) :: A(nrows,ncols), x(ncols)
        integer, intent(out) :: b(nrows)
        integer :: i, j

        do i = 1, nrows
            b(i) = 0
            do j = 1, ncols
                b(i) = b(i) + A(i,j) * x(j)
            end do
        end do
    end subroutine matvec

    subroutine matvecrev(A, x, b, nrows, ncols)
        integer, intent(in) :: nrows, ncols
        integer, intent(in) :: A(nrows,ncols), x(ncols)
        integer, intent(out) :: b(nrows)
        integer :: i, j

        do j = 1, nrows
            b(j) = 0
            do i = 1, ncols
                b(j) = b(j) + A(i,j) * x(j)
            end do
        end do
    end subroutine matvecrev

end program MatrixProduct
