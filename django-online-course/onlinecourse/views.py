from django.shortcuts import render, get_object_or_404, redirect
from django.contrib.auth.decorators import login_required
from django.views.decorators.http import require_POST
from .models import Course, Submission


def course_details(request, course_id):
    course = get_object_or_404(Course, pk=course_id)
    return render(request, "onlinecourse/course_details_bootstrap.html", {
        "course": course
    })


@login_required
@require_POST
def submit(request, course_id):
    course = get_object_or_404(Course, pk=course_id)
    questions = course.questions.prefetch_related("choices")
    score = 0
    total = questions.count()

    for question in questions:
        selected_id = request.POST.get(f"question_{question.id}")
        if selected_id and question.choices.filter(
            id=selected_id, is_correct=True
        ).exists():
            score += 1

    submission = Submission.objects.create(
        user=request.user,
        course=course,
        score=score,
        total_questions=total,
    )
    return redirect("show_exam_result", submission_id=submission.id)


@login_required
def show_exam_result(request, submission_id):
    submission = get_object_or_404(
        Submission.objects.select_related("course", "user"),
        pk=submission_id,
        user=request.user,
    )
    questions = submission.course.questions.prefetch_related("choices")
    results = []

    for question in questions:
        selected_id = request.session.get(
            f"question_{question.id}"
        )
        results.append({
            "question": question,
            "correct_choices": question.choices.filter(is_correct=True),
            "selected_id": selected_id,
        })

    return render(request, "onlinecourse/exam_result.html", {
        "submission": submission,
        "results": results,
    })
